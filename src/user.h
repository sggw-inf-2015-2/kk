#ifndef USER_H
#define USER_H
#include <QObject>
#include <QString>
#include <QUuid>
#include <Qfile>
#include <QTextStream>
#include <QMessageBox>
#include <String>
#include <QException>
#include <exception>
#include <stdexcept>

enum gender {women=0,man=1};

/**
 * @brief Store and manage all data about players (users) how shouts
 */
class User : public QObject
{
    Q_OBJECT
    private:

        static QList<User> registeredUsers;
        QString firstName;
        QString lastName;
        gender personGender;
        double shoutScore;
        bool attemptedRepeat;
    public:

        QUuid getId();
        User& operator =(const User&);//?
        User(const User& user);
        User(const QString &firstName,const QString &lastName);
        User(const QString &firstName,const QString &lastName,gender personGender);
        User(const QString &firstName,const QString &lastName, gender gender,double score);
        static void editUser(int ID,const QString &firstName, const QString &lastName, gender personGender);
        void setShoutScore(double score);
        float getShoutScore();
        static void exportToCSV(const QString &fileName);
        static void importFromCSV(const QString &fileName);
        static void TEST();//This function is just for me. Should be remove at the end.
    signals:

    public slots:
};

#endif // USER_H
