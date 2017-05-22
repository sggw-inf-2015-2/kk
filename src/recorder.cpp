#include "recorder.h"
#include <QDir>
#include <QAudioFormat>
#include <QTimer>
#include <stdexcept>

using std::logic_error;

Recorder::Recorder()
{
	initialiseRecorder();
	setupTimer();
}

Recorder::~Recorder()
{
    if (audio != nullptr)
        delete audio;
}

void Recorder::initialiseRecorder()
{
	setFormatSettings();
	QAudioDeviceInfo device = QAudioDeviceInfo::defaultInputDevice();
	if (!device.isFormatSupported(format))
	{
		qDebug() << "Format not supported, trying to use the nearest.";
		format = device.nearestFormat(format);
	}
	audio = new QAudioInput(format);
}

void Recorder::setupTimer()
{
	timer.setSingleShot(true);
	timer.setInterval(5000);
	connect(&timer, SIGNAL(timeout()), this, SLOT(Stop()));
}

void Recorder::setFormatSettings()
{
	format.setChannelCount(1);
	format.setSampleRate(48000);
	format.setCodec("audio/pcm");
	format.setSampleSize(16);
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);
}

void Recorder::Start()
{
	try
	{
		openFile("audiodata.wav");
	}
	catch (exception &)
	{
		throw;
		return;
	}
	audio->start(&file);

	// Record 5 seconds.
	timer.start();
}

void Recorder::openFile(const QString &fileName)
{
	// Check whether some directory with the same name already exist.
	QDir testDir(fileName);
	if (testDir.exists())
	{
		QString msg = QString("Nie udało się utworzyć pliku. Istnieje już katalog o tej samej nazwie (%1).").arg(fileName);
		throw logic_error(msg.toStdString());
		return;
	}

	QDir dir;
	QString path = dir.absoluteFilePath(fileName);
	file.setFileName(path);
	file.setAudioFormat(format);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		QString msg = "Nie udało się otworzyć pliku. ";
		msg.append(file.errorString());
		throw logic_error(msg.toStdString());
		return;
	}
}

void Recorder::Stop()
{
	timer.stop(); // Stop a timer in case user aborts recording.
	audio->stop();
	closeFile();

	emit recordingStopped(file.size());
}

void Recorder::closeFile()
{
	file.close();
}

void Recorder::printAvailableDevices()
{
    auto devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    int i = 1;
    for (auto device : devices)
    {
        qDebug() << QString("Urządzenie %1 ").arg(i) << device.deviceName();
        qDebug() << "Supported sample sizes:";
        for (auto sampleSize : device.supportedSampleSizes())
        {
            qDebug() << sampleSize;
        }
        qDebug() << "Supported sample rates:";
        for (auto sampleRate : device.supportedSampleRates())
        {
            qDebug() << sampleRate;
        }
		qDebug() << "Supported codecs:";
		for (auto codecs : device.supportedCodecs())
		{
			qDebug() << codecs;
		}
		qDebug() << "Supported channel counts:";
		for (auto channelCount : device.supportedChannelCounts())
		{
			qDebug() << channelCount;
		}
		qDebug() << "Supported sample types:";
		for (auto sampleType : device.supportedSampleTypes())
		{
			qDebug() << sampleType;
		}
		qDebug() << "Supported byte orders:";
		for (auto byteOrder : device.supportedByteOrders())
		{
			qDebug() << byteOrder;
		}
        qDebug() << "\n";
        ++i;
    }
}
