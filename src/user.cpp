#include "user.h"
QList<User> User::registeredUsers;

User::User(const QString &firstName,const QString &lastName, gender personGender=gender::empty,double score=0)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->personGender=personGender;
    this->shoutScore=score;
    User::registeredUsers.append(*this);
}

double User::getShoutScore()
{
    return shoutScore;
}

QString User::getFirstName()
{
    return firstName;
}

QString User::getLastName()
{
    return lastName;
}

gender User::getPersonGernder()
{
    return personGender;
}

/**
 * @brief User::setShoutScore
 * @param id
 * @param score
 * @throw if id is out of bound (less then zero or bigger then users number)
 */
void User::setShoutScore(int id,double score)
{
    if (id<0 || id>registeredUsers.size()) throw std::logic_error( "0<id<users, yours id:"+id );
    registeredUsers[id].shoutScore=score;
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
            stream << u.firstName<<";"<<u.lastName<<";"<<u.personGender<<";"<<QString::number(u.shoutScore) <<""<< endl;
       }
   }else{
       throw std::logic_error( "File not open to write! (meaby you don't have permission)" );
   }
   file.close();
}

/**
 * @brief User::importFromCSV - load data about all pleaers (users) to Qlist
 * @warning removes all exesting users in Qlist, without warning
 * @param fileName
 */
QList<User*> User::importFromCSV(const QString &fileName)
{
    registeredUsers.clear();

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        throw std::logic_error( "File not open to read! (meaby not exist)" );
    }
    QTextStream in(&file);
    QList<User*> list;
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");
        QString firstName = fields.at(0);
        QString lastName = fields.at(1);
        gender personGender = (gender) fields.at(2).toInt();
        double score = fields.at(3).toDouble();
        User user(firstName,lastName,personGender,score);
        list.append(&registeredUsers.back());
    }
    file.close();
    return list;
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


//void User::TEST()
//{
//    User user1("a","b",gender::women);
//    User user2("c","d",gender::women);
//    User user3("e","f");
//    User user4("g","h",gender::man,2.3);
//    exportToCSV("mojiUserzy");
//    QList<User*> list = importFromCSV("mojiUserzy");
//    qDebug()<<"list: "<<list.size();
//    for (int i=0;i<list.size();i++){
//        qDebug()<<list[i]->getFirstName()<<" "<<list[i]->getLastName()<<" "<<list[i]->getPersonGernder()<<" "<<list[i]->getShoutScore()<<" ";
//    }
//}
