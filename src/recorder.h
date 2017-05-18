#ifndef RECORDER_H
#define RECORDER_H

#include <QAudioInput>
#include <QFile>
#include <QDebug>
#include <exception>
#include <QTimer>

using std::exception;

class Recorder : public QObject
{
	Q_OBJECT
    QAudioInput *audio;
	QFile file;
   // QTimer *timer;


    void setFormatSettings(QAudioFormat *format);
	void openFile();
	void closeFile();
public:
  //  QTimer *timer;
	Recorder();
    ~Recorder();
    void Start();
public slots:
    void Stop();
signals:
	void bytesSaved(qint64 bytes);
};

#endif // RECORDER_H
