#include "recorder.h"
#include <stdexcept>
#include <QDir>

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
    foreach(auto device, info.availableDevices(QAudio::AudioInput))
    {
        qDebug() << device.deviceName();
    }

	if (!info.isFormatSupported(format)) // jeśli określony w funkcji setFormatSettings format nie jest obsługiwany, używany jest domyślny
    {
		qDebug() << "Format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
    }
    audio = new QAudioInput(format);
	try
	{
		openFile();
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

void Recorder::setFormatSettings(QAudioFormat *format)
{
    format->setChannelCount(1);
	format->setSampleRate(48000);
    format->setCodec("audio/pcm");
	format->setSampleSize(16);
}

void Recorder::openFile()
{
    QDir dir;
    QString path = dir.absoluteFilePath("audiotest.raw");
	file.setFileName(path);
    //file.open()
    /*if (!file.exists())
	{
		QString msg = "Nie udało się utworzyć pliku. ";
		msg.append(file.errorString());
        throw std::logic_error(msg.toStdString());
		return;
    }*/
	
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
	{
		QString msg = "Nie udało się otworzyć pliku. ";
		msg.append(file.errorString());
        throw std::logic_error(msg.toStdString());
	}
	
}

void Recorder::closeFile()
{
	file.close();
}
