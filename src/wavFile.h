#ifndef WAVFILE_H
#define WAVFILE_H
#include <QFile>
#include <QAudioFormat>

class WavFile : public QFile
{
	QAudioFormat format;

	void writeHeader();
	bool isFormatSupported();
public:
	WavFile() : QFile() {}
	void setAudioFormat(const QAudioFormat &format) { this->format = format; }
	bool open(OpenMode flags) override;
	void close() override;
};

#endif // WAVFILE_H
