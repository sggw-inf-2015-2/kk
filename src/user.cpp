#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}

static void User::addUser(QString firstName, QString lastName)
{
    QUuid newId = new QUuid();
    registeredUsers.append(User());
}

void User::setShoutScore(float score)
{
    shoutScore = score;
}
