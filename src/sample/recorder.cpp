#include "recorder.h"
#include <QDir>
#include <QAudioFormat>
#include <stdexcept>

using std::logic_error;

Recorder::Recorder()
{
	audio = nullptr;
}

Recorder::~Recorder()
{
    if (audio != nullptr)
        delete audio;
}

void Recorder::Start()
{
    QAudioFormat format;
    setFormatSettings(&format);
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
	if (!info.isFormatSupported(format)) // jeśli określony w funkcji setFormatSettings format nie jest obsługiwany, używany jest domyślny
    {
        qDebug() << "Format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
    }
    audio = new QAudioInput(format);
	try
	{
		openFile("audiodata");
	}
	catch (exception &)
	{
		throw;
		return;
	}
	audio->start(&file);
}

void Recorder::Stop()
{
	emit bytesSaved(file.size());

    audio->stop();
	closeFile();
    delete audio;
    audio = nullptr;
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

void Recorder::setFormatSettings(QAudioFormat *format)
{
	format->setChannelCount(1);
    format->setSampleRate(48000);
    format->setCodec("audio/pcm");
	format->setSampleSize(16);
	format->setByteOrder(QAudioFormat::LittleEndian);
	format->setSampleType(QAudioFormat::SignedInt);
}

void Recorder::openFile(const QString &fileName)
{
	// Sprawdzenie, czy w katalogu z aplikacją nie znajduje się folder o takiej samej nazwie
	QDir testDir(fileName);
	if (testDir.exists())
	{
		QString msg = QString("Nie udało się utworzyć pliku. Istnieje już katalog o tej samej nazwie (%1).").arg(fileName);
		throw logic_error(msg.toStdString());
	}

	QDir dir;
	QString path = dir.absoluteFilePath(fileName);
    file.setFileName(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		QString msg = "Nie udało się otworzyć pliku. ";
		msg.append(file.errorString());
        throw logic_error(msg.toStdString());
	}
}
void Recorder::closeFile()
{
	file.close();
}
