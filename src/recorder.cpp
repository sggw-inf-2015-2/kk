#include "recorder.h"
#include <QDir>
#include <QAudioFormat>
#include <limits>

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
    buffer.buffer().clear(); // Flush data from underlying QByteArray internal buffer.
    buffer.open(QIODevice::ReadWrite);
    audio->start(&buffer);

	// Record 5 seconds.
    timer.start();
}

void Recorder::Stop()
{
    timer.stop(); // Stop a timer in case user aborts recording.
    audio->stop();
	buffer.close();

	parseBufferContent(buffer.data());
	emit recordingStopped(complexData);
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
	QDataStream stream(data);
	parse(stream);
}

void Recorder::LoadAudioDataFromFile(const QString &fileName)
{
    QFile file(fileName);
    file.open(QFile::ReadOnly);
	file.seek(44); // Skip WAV header.
    QDataStream fstream(&file);
	parse(fstream);
    file.close();
    emit recordingStopped(complexData);
}

void Recorder::parse(QDataStream &stream)
{
	complexData.clear();
	stream.setByteOrder(QDataStream::LittleEndian);
	while (!stream.atEnd())
	{
		short i;
		stream >> i;
		double j = (double) i / (double) std::numeric_limits<short>::max(); // Scale to [-1,1] range.
		complexData.push_back(std::complex<double>(j, 0.0));
	}
}
