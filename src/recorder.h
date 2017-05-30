#ifndef RECORDER_H
#define RECORDER_H

#include <QAudioInput>
#include "wavFile.h"
#include <QDebug>
#include <QTimer>
#include <QStringList>
#include <exception>

using std::exception;

class Recorder : public QObject
{
	Q_OBJECT
	QAudioFormat format;
    QAudioInput *audio;
	WavFile file;
	QTimer timer;

	void setupTimer();
	void setFormatSettings();
	void openFile(const QString &fileName);
	void closeFile();
    void printFormat() const;
public:
	Recorder();
    ~Recorder();
    void Start();
	QStringList GetAvailableDevices() const;
public slots:
	void Stop();
	void InitialiseRecorder(const QString &deviceName = "");
signals:
	void recordingStopped(qint64 savedBytes);
};

#endif // RECORDER_H
