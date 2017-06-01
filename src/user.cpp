#include "user.h"
QList<User> User::registeredUsers;

//???
//User& User::operator =(const User& user) {
//    //User& u = user(user.firstName,user.lastName,user.personGender);
//    this->firstName="operator =";
//    return *this;
//}

//copy constructor use by Qlist internal functions
User::User(const User &user) : QObject()
{
    this->firstName=user.firstName;
    this->lastName=user.lastName;
    this->personGender=user.personGender;
    this->shoutScore=user.shoutScore;
}

User::User(const QString &firstName,const QString &lastName, gender personGender) : QObject()
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->personGender=personGender;
    User u = *this;
    User::registeredUsers.append(u);
}

User::User(const QString &firstName,const QString &lastName, gender personGender,double score) : QObject()
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->personGender=personGender;
    this->shoutScore=score;
    User::registeredUsers.append(*this);
}

float User::getShoutScore()
{
    return shoutScore;
}

void User::setShoutScore(double score)
{
    shoutScore = score;
}

/**
 * @brief User::exportToCSV save all data about players (users) in file
 * @warning overwrite existing file, without warning
 * @param fileName
 */
void User::exportToCSV(const QString &fileName)
{
   QString filename = fileName;
   QFile file(filename);
   if (file.open(QIODevice::ReadWrite  | QIODevice::Truncate)) {
   QTextStream stream(&file);
       foreach (User u, User::registeredUsers) {
            stream << u.firstName<<","<<u.lastName<<","<<u.personGender<<","<<QString::number(u.shoutScore) <<""<< endl;
       }
   }
   file.close();
}

/**
 * @brief User::importFromCSV - load data about all pleaers (users) to Qlist
 * @warning removes all exesting users in Qlist, without warning
 * @param fileName
 */
void User::importFromCSV(const QString &fileName)
{
    registeredUsers.clear();

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
       //QException e =new QException();
       //e.what();
        throw std::logic_error( "received negative value" );
        //QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        QString firstName = fields.at(0);
        QString lastName = fields.at(1);
        gender personGender = (gender) fields.at(2).toInt();
        double score = fields.at(3).toDouble();
        User user(firstName,lastName,personGender,score);
    }
    file.close();
    return;
}

/**
 * @brief User::editUser replace all data about user, except score
 * @param ID index on Qlist (which user edit)
 */
void User::editUser(int ID, const QString &firstName, const QString &lastName, gender personGender)
{
    User &u = User::registeredUsers[ID];
    u.firstName = firstName;
    u.lastName = lastName;
    u.personGender = personGender;
}

//This function is just for me. Should be remove at the end.
void User::TEST()
{
     User a("Jan","Kowalski",gender::women,1.21);
     User b("Ala","Nowak",gender::women,3.42);
     User c("Arek","Zot",gender::man,5.63);
     //registeredUsers[0].setShoutScore(100);
     User::exportToCSV("Data.csv");
     User::importFromCSV("Data2.csv");

    // registeredUsers[1].setShoutScore(15.3);
    // registeredUsers[2].setShoutScore(11.002);

     QTextStream out(stdout);
     //out<<a.firstName<<endl;
     //registeredUsers.append(a);
     out<<"--->"<<registeredUsers.count()<<"<---"<<endl;
     out<<registeredUsers.at(0).firstName<<registeredUsers[0].shoutScore<<endl;
     out<<registeredUsers.at(1).firstName<<endl;
     out<<registeredUsers.at(2).firstName<<endl;
     //out<<registeredUsers.at(3).firstName<<endl;
     out<<"+++"<<endl;
     User::editUser(0,"OLEK","Janecki",gender::women);
     out<<registeredUsers.at(0).firstName<<endl;
     out<<registeredUsers.at(0).lastName<<endl;
     out<<registeredUsers.at(0).personGender<<endl;
     out<<registeredUsers.at(0).shoutScore<<endl;
//     User::exportToCSV();

}
