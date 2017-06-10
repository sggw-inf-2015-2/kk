#include "user.h"
QList<User> User::registeredUsers;

/**
 * @brief Konstruktor. Tworzy obiekt użytnikownika i dodaje go do listy wszystkich użytkowników.
 * @param firstName Imię użytkownika.
 * @param lastName Nazwisko użytkownika.
 * @param personGender Płeć użytkownika. Domyślną wartością jest mężczyzna (gender::man).
 * @param score Wynik użytkownika. Domyślną wartością jest 0.
 * @warning Nie należy tworzyć obiektów typu User w celu innym, niż dodanie nowego użytkownika w programie. Takie zachowanie prowadzi do powstawania
 * duplikatów w statycznej liście użytkowników.
 * @author Jarosław Tomczyński
 */
User::User(const QString &firstName,const QString &lastName, gender personGender=man,double score=0.0)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->personGender=personGender;
    this->shoutScore=score;
    User::registeredUsers.append(*this);
}

/**
 * @brief Zwraca poziom krzyku użytkownika.
 * @return Poziom krzyku użytkownika.
 * @author Jarosław Tomczyński
 */
double User::getShoutScore()
{
    return shoutScore;
}

/**
 * @brief Zwraca imię użytkownika.
 * @return Imię użytkownika.
 * @author Jarosław Tomczyński
 */
QString User::getFirstName()
{
    return firstName;
}

/**
 * @brief Zwraca nazwisko użytkownika.
 * @return Nazwisko użytkownika.
 * @author Jarosław Tomczyński
 */
QString User::getLastName()
{
    return lastName;
}

/**
 * @brief Zwraca płeć użytkownika.
 * @return Płeć użytkownika. Możliwe wartości: gender::man, gender::woman.
 * @author Jarosław Tomczyński
 */
gender User::getPersonGender()
{
    return personGender;
}

/**
 * @brief Przypisuje użytkownikowi znajdującemu się w określonym indeksie określony poziom krzyku.
 * @param id Indeks użytkownika w statycznej liście użytkowników.
 * @param score Poziom krzyku użytkownika.
 * @throw std::logic_error Jeśli indeks jest mniejszy od 0 lub równy/większy do rozmiaru listy.
 * @author Jarosław Tomczyński
 */
void User::setShoutScore(int id,double score)
{
    if (id<0 || id>registeredUsers.size())
    {
        throw std::logic_error("Indeks poza zakresem listy.");
        return;
    }
    registeredUsers[id].shoutScore=score;
}

/**
 * Zapisuje dane o wszystkich użytkownikach w pliku o formacie CSV (comma-separated values, wartości rozdzielone przecinkiem).
 * Dane zapisywane są w kolejności: imię, nazwisko, płeć, poziom krzyku.
 * Płeć zapisywana jest w formacie liczbowym, gdzie 0 oznacza kobietę, a 1 mężczyznę.
 *
 * @brief Zapisuje dane o wszystkich użytkownikach w pliku CSV.
 * @warning Jeśli plik o podanej nazwie już istnieje, plik ten zostanie nadpisany.
 * @param fileName Nazwa pliku z rozszerzeniem csv.
 * @throw std::logic_error Jeśli użytkownik nie ma uprawnień do zapisu w podanym miejscu lub z powodu innego błędu uniemożliwiającego otwarcie
 * pliku do zapisu.
 * @author Jarosław Tomczyński
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
       throw std::logic_error("Nie udało się utworzyć pliku. Upewnij się, że masz odpowiednie uprawnienia.");
   }
   file.close();
}

/**
 * Pobiera dane o użytkownikach z pliku CSV i dodaje ich do statycznej listy użytkowników. Funkcja nie dodaje nowych wpisów
 * do tabeli w oknie administratora i do rankingu.
 *
 * @brief Pobiera dane o użytkownikach z pliku CSV i dodaje ich do statycznej listy użytkowników.
 * @warning Usuwa wszystkich znajdujących się wcześniej na liście użytkowników.
 * @param fileName Nazwa pliku z rozszerzeniem csv.
 * @return Zwraca listę wskaźników na typ User, zawierającą adresy wstawionych do statycznej listy użytkowników.
 * @throw std::logic_error Jeśli użytkownik nie ma uprawnień do otwarcia pliku lub z powodu innego błędu uniemożliwiającego otwarcie
 * pliku.
 * @author Jarosław Tomczyński
 */
QList<User*> User::importFromCSV(const QString &fileName)
{
    registeredUsers.clear();

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        throw std::logic_error("Nie udało się utworzyć pliku. Upewnij się, że masz odpowiednie uprawnienia.");
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
 * @brief Zwraca adres obiektu User znajdującego się w określonym indeksie w statycznej liście.
 * @param id Indeks użytkownika w statycznej liście użytkowników.
 * @return Adres obiektu User.
 * @throw std::logic_error Jeśli indeks jest mniejszy od 0 lub równy/większy do rozmiaru listy.
 * @author Marcin Anuszkiewicz
 */
User *User::GetUser(int index)
{
    if (index<0 || index>registeredUsers.size())
    {
        throw std::logic_error("Indeks poza zakresem listy.");
        return nullptr;
    }
    return &User::registeredUsers[index];
}

/**
 * @brief Edytuje wszystkie dane o użytkowniku znajdującemu się w statycznej liście użytkowników z wyjątkiem poziomu krzyku.
 * @param id Indeks użytkownika w statycznej liście użytkowników.
 * @param firstName Imię użytkownika.
 * @param lastName Nazwisko użytkownika.
 * @param personGender Płeć użytkownika.
 * @author Jarosław Tomczyński
 */
void User::editUser(int ID, const QString &firstName, const QString &lastName, gender personGender)
{
    User &u = User::registeredUsers[ID];
    u.firstName = firstName;
    u.lastName = lastName;
    u.personGender = personGender;
}

