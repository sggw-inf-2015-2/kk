#ifndef AUDIOMODEL_H
#define AUDIOMODEL_H

#include <QObject>

class AudioModel : public QObject
{
    Q_OBJECT
public:
    explicit AudioModel(QObject *parent = 0);

signals:

public slots:
};

#endif // AUDIOMODEL_H
