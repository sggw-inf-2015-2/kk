#ifndef USER_H
#define USER_H
#include <QString>
#include <Qfile>
#include <QTextStream>
#include <exception>
#include <stdexcept>
//#include <QDebug>

enum gender {women,man,empty};

/**
 * @brief Store and manage all data about players (users) how shouts
 */
class User
{
    private:
        static QList<User> registeredUsers;
        QString firstName;
        QString lastName;
        gender personGender;
        double shoutScore;
        bool attemptedRepeat;
    public:
        User(const QString &firstName,const QString &lastName, gender gender,double score);
        static void editUser(int ID,const QString &firstName, const QString &lastName, gender personGender);
        static void setShoutScore(int id,double score);
        double getShoutScore();
        QString getFirstName();
        QString getLastName();
        gender getPersonGernder();
        static void exportToCSV(const QString &fileName);
        static QList<User*> importFromCSV(const QString &fileName);

        //static void TEST();
};

#endif // USER_H
