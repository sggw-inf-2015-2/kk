#ifndef RECORDER_H
#define RECORDER_H

#include <QAudioInput>
#include "wavFile.h" // To be deleted in final release.
#include <QDebug>
#include <QTimer>
#include <QBuffer>
#include <QStringList>
#include <exception>
#include <complex>

using std::exception;

class Recorder : public QObject
{
    Q_OBJECT
    QAudioFormat format;
    QAudioInput *audio;
    // To be deleted in final release:
	 WavFile file;
    //
    QBuffer buffer;
    QTimer timer;
	QVector<std::complex<double> > complexData;

	void setupTimer();
	void setFormatSettings();
	void openFile(const QString &fileName);
	void closeFile();
    void printFormat() const;
	void parseBufferContent(const QByteArray &data);
    void loadAudioDataFromFile(const QString &fileName);
public:
	Recorder();
    ~Recorder();
    void Start();
	QStringList GetAvailableDevices() const;
public slots:
	void Stop();
	void InitialiseRecorder(const QString &deviceName = "");
signals:
	void recordingStopped(const QVector<std::complex<double> > &complexData);
};

#endif // RECORDER_H
