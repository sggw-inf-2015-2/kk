#ifndef RECORDER_H
#define RECORDER_H

#include <QAudioInput>
#include <QDebug>
#include <QBuffer>
#include <QObject>

class Recorder : public QObject
{
	Q_OBJECT

    QAudioInput *audio;
	QBuffer buffer;

    void setFormatSettings(QAudioFormat *format);
    void openBuffer();
    void closeBuffer();
public:
	Recorder();
    ~Recorder();
    void Start();
    void Stop();
signals:
	void bytesSaved(int bytes);
private slots:
	void sendSavedBytes();
};

#endif // RECORDER_H
