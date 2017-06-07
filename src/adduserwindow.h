#ifndef ADDUSERWINDOW_H
#define ADDUSERWINDOW_H

#include <QDialog>
#include "user.h"

namespace Ui {
class AddUserWindow;
}

class AddUserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserWindow(QWidget *parent = 0);
    AddUserWindow(QWidget *parent,QString FirstName, QString SurName, QString g);
    void accept() override;
    QString GetName() {return name;}
    QString GetSurName() {return surname;}
    gender GetGender() {return g;}
    bool GetSaved() {return saved;}
    ~AddUserWindow();

private:
    Ui::AddUserWindow *ui;
    QString name;
    QString surname;
    gender g;
    bool saved;
};

#endif // ADDUSERWINDOW_H
