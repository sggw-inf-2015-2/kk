#include "recorder.h"

Recorder::Recorder()
{
	audio = nullptr;
	connect(&buffer, SIGNAL(readyRead()), this, SLOT(sendSavedBytes()));
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
        qDebug() << "Default format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
    }
    audio = new QAudioInput(format);
    openBuffer();
    audio->start(&buffer);
}

void Recorder::Stop()
{
    audio->stop();
    closeBuffer();
    delete audio;
	audio = nullptr;
}

void Recorder::setFormatSettings(QAudioFormat *format)
{
    format->setChannelCount(1);
	format->setSampleRate(8000);
    format->setCodec("audio/pcm");
	format->setSampleSize(16);
}

void Recorder::openBuffer()
{
    buffer.open(QBuffer::ReadWrite);
}

void Recorder::closeBuffer()
{
	buffer.buffer().clear();
	buffer.close();
}

void Recorder::sendSavedBytes()
{
	emit bytesSaved((int)buffer.size());
}

