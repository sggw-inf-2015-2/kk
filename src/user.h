#ifndef USER_H
#define USER_H

#include <QObject>
#include <QUuid>

class User : public QObject
{
    Q_OBJECT

    static QList<User> registeredUsers;

    QString firstName;
    QString lastName;
    float shoutScore;
    QUuid id;

public:
    explicit User(QObject *parent = 0);

    static void addUser(QString firstName, QString lastName);
    static void removeUser(QUuid id);

    QUuid getId();
    float getShoutScore();

    void save();

signals:

public slots:
    void setShoutScore(float score);
};

#endif // USER_H
