#ifndef RECORDER_H
#define RECORDER_H

#include <QAudioInput>
#include <QFile>
#include <QDebug>
#include <exception>
using std::exception;

class Recorder : public QObject
{
	Q_OBJECT
    QAudioInput *audio;
	QFile file;

    void printAvailableDevices();
    void setFormatSettings(QAudioFormat *format);
	void openFile(const QString &fileName);
	void closeFile();
public:
	Recorder();
    ~Recorder();
    void Start();
    void Stop();
signals:
	void bytesSaved(qint64 bytes);
};

#endif // RECORDER_H
