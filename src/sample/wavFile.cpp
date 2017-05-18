#include "wavFile.h"
#include <QDataStream>

void WavFile::writeHeader()
{
	QDataStream out(this);
	out.setByteOrder(QDataStream::LittleEndian);

	// Marks the file as a riff file.
	out.writeRawData("RIFF", 4);
	// Size of the overall file (filled by close()).
	out << quint32(0);
	// File Type Header
	out.writeRawData("WAVE", 4);
	// Format chunk marker. Includes trailing null.
	out.writeRawData("fmt ", 4);
	// "fmt " chunk size (always 16 for PCM).
	out << quint32(16);
	// Data format (1 => PCM).
	out << quint16(1);
	out << quint16(format.channelCount());
	out << quint32(format.sampleRate());
	// (Sample Rate * BitsPerSample * Channels) / 8
	out << quint32(format.sampleRate() * format.channelCount() * format.sampleSize() / 8 );
	// BitsPerSample * Channels
	out << quint16(format.channelCount() * format.sampleSize() / 8);
	// BitsPerSample
	out << quint16(format.sampleSize());
	// "data" chunk header. Marks the beginning of the data section.
	out.writeRawData("data", 4);
	// Placeholder for the data chunk size (filled by close()).
	out << quint32(0);

	Q_ASSERT(pos() == 44); // Must be 44 for WAV PCM.
}

bool WavFile::isFormatSupported()
{
	return
	(format.sampleSize() == 8 && format.sampleType() == QAudioFormat::UnSignedInt)
	||
	(format.sampleSize() > 8 && format.sampleType() == QAudioFormat::SignedInt && format.byteOrder() == QAudioFormat::LittleEndian);
}

bool WavFile::open(QIODevice::OpenMode flags)
{
	if (!isFormatSupported())
	{
		setErrorString(tr("Pliki WAV nie obsługują podanego formatu. "));
		return false;
	}
	if (!QFile::open(flags))
		return false;
	writeHeader();
	return true;
}

void WavFile::close()
{
	quint32 fileSize = size();

	QDataStream out(this);
	// Set the same ByteOrder like in writeHeader()
	out.setByteOrder(QDataStream::LittleEndian);
	// fill RIFF chunk size
	seek(4);
	out << quint32(fileSize - 8);

	// fill data chunk size
	seek(40);
	out << quint32(fileSize - 44);

	QFile::close();
}
