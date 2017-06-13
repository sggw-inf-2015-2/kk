#include "recorder.h"
#include <QDir>
#include <QAudioFormat>
#include <QDataStream>

using std::logic_error;

Recorder::Recorder()
{
    audio = nullptr;
	InitialiseRecorder();
	setupTimer();
}

Recorder::~Recorder()
{
    if (audio != nullptr)
        delete audio;
}

void Recorder::InitialiseRecorder(const QString &deviceName)
{
	// destroy old QAudioInput object (if exist)
	if (audio != nullptr)
		delete audio;

	QAudioDeviceInfo device;
    if (deviceName.isEmpty())
		device = QAudioDeviceInfo::defaultInputDevice();
	else
	{
		for (auto inputDevice : QAudioDeviceInfo::availableDevices(QAudio::AudioInput))
		{
			if (inputDevice.deviceName() == deviceName)
			{
				device = inputDevice;
				break;
			}
		}
	}

    setFormatSettings();
	if (!device.isFormatSupported(format))
	{
		qDebug() << "Format not supported, trying to use the nearest.";
		format = device.nearestFormat(format);
	}
	printFormat();
    audio = new QAudioInput(device, format);
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
    // to be deleted in final release:
//	try
//	{
//		openFile("audiodata.wav");
//	}
//	catch (exception &)
//	{
//		throw;
//		return;
//	}
    //buffer.buffer().clear(); // Flush data from underlying QByteArray internal buffer.
    //buffer.open(QIODevice::ReadWrite);
    //audio->start(&buffer);

	// Record 5 seconds.
    //timer.start();
    Stop();
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
    //timer.stop(); // Stop a timer in case user aborts recording.
    //audio->stop();
    //buffer.close();

    // parseBufferContent(buffer.data());
    loadAudioDataFromFile("kalibracja.wav");
	emit recordingStopped(complexData);
}

void Recorder::closeFile()
{
    file.close();
}

void Recorder::printFormat() const
{
	qDebug() << "Channel count: " << format.channelCount();
	qDebug() << "Byte order: " << format.byteOrder();
	qDebug() << "Sample type: " << format.sampleType();
	qDebug() << "Sample size: " << format.sampleSize();
	qDebug() << "Sample rate: " << format.sampleRate();
    qDebug() << "";
}

QStringList Recorder::GetAvailableDevices() const
{
    auto devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
	QStringList devicesNames;
    for (auto device : devices)
    {
		devicesNames.append(device.deviceName());
    }
	return devicesNames;
}

void Recorder::parseBufferContent(const QByteArray &data)
{
	complexData.clear();
	QDataStream stream(data);
	while (!stream.atEnd())
	{
        short i;
		stream >> i;
		complexData.push_back(std::complex<double>((double)i, 0.0));
    }
}

void Recorder::loadAudioDataFromFile(const QString &fileName)
{
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QDataStream fstream(&file);
    while (!fstream.atEnd())
    {
        short i;
        fstream >> i;
        complexData.push_back(std::complex<double>((double)i, 0.0));
    }
    file.close();
}
