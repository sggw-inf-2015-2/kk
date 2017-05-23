#ifndef USER_H
#define USER_H
#include <QObject>
#include <QString>
#include <QUuid>
#include <Qfile>
#include <QTextStream>
#include <QMessageBox>
#include <String>

class User : public QObject
{
    Q_OBJECT
    enum gender {kobieta=0,mezczyzna=1};
    private:
        static QList<User*> registeredUsers;
        QString firstName;
        QString lastName;
        gender personGender;
        double shoutScore;
        bool attemptedRepeat;
        //QUuid id;
        //int id;
    public:

        QUuid getId();
        User(QString firstName,QString lastName);
        User(QString firstName,QString lastName,gender personGender);
        User(QString firstName, QString lastName, gender gender,double score);
        void setShoutScore(float score);
        //void addUserToList();
        //QUuid getId();
        static void createUser(QString firstName,QString lastName,gender personGender);
        static void editUser(int ID,QString firstName, QString lastName, gender personGender);
        float getShoutScore();
        void setScore(double score);
        static void exportToCSV();
        static QList<User*> importFromCSV();
        static void TEST();
        //QList<User> getAllUsers();
        //void repeat();
    signals:

    public slots:
};

#endif // USER_H
