#include "user.h"
QList<User*> User::registeredUsers;

User::User(QString firstName, QString lastName)
{
    this->firstName = firstName;
    this->lastName = lastName;

}

User::User(QString firstName, QString lastName, gender personGender)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->personGender=personGender;
    //QUuid newId = new QUuid();
}

User::User(QString firstName, QString lastName, gender personGender,double score)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->personGender=personGender;
    this->shoutScore=score;
    //QUuid newId = new QUuid();
}

float User::getShoutScore()
{
    return shoutScore;
}

void User::exportToCSV()
{
   QString filename = "Data.csv";
   QFile file(filename);
   if (file.open(QIODevice::ReadWrite)) {
   QTextStream stream(&file);
    foreach (User* u, User::registeredUsers) {
        stream << u->firstName<<","<<u->lastName<<","<<u->personGender<<","<<u->shoutScore <<""<< endl;
    }
   }
}

QList<User*> User::importFromCSV()
{
    QFile file("Data.csv");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        QString firstName = fields.at(0);
        QString lastName = fields.at(1);
        gender personGender;
//        if (fields.at(2)=="1"){
//            personGender = 1;
//        }
        int score = fields.at(3).toInt();
        User* user = new User(firstName,lastName,personGender,score);
        User::registeredUsers.append(user);
    }

    file.close();
    return User::registeredUsers;
}

void User::TEST()
{


//     User::createUser("Jan","Kowalski",false);
//     User::createUser("Ala","Nowak",true);
     //User::createUser("Arek","Zot",false);

//     User::exportToCSV();
     User::importFromCSV();
     QTextStream out(stdout);
     out<<"--->"<<registeredUsers.count()<<"<---";
     out<<registeredUsers.at(0)->firstName<<endl;
     out<<registeredUsers.at(1)->firstName<<endl;
     out<<registeredUsers.at(2)->firstName<<endl;

     //User::editUser(0,"OLEK","Janecki",true);
     out<<registeredUsers.at(0)->firstName<<endl;
     out<<registeredUsers.at(0)->lastName<<endl;
     out<<registeredUsers.at(0)->shoutScore<<endl;
     User::exportToCSV();
//     foreach (User* u, User::registeredUsers) {
//         out<<(u->firstName);
//     }
}

void User::setShoutScore(float score)
{
    shoutScore = score;
}



void User::createUser(QString firstName, QString lastName, gender personGender)
{
    User* user = new User(firstName,lastName,personGender);
    User::registeredUsers.append(user);
}

void User::editUser(int ID, QString firstName, QString lastName, gender personGender)
{
    User* u = User::registeredUsers.at(0);
    u->firstName = firstName;
    u->lastName = lastName;
    u->personGender = personGender;
}
