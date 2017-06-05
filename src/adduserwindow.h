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
    void accept() override;
    QString GetName() {return name;}
    QString GetSurName() {return surname;}
    gender GetGender() {return g;}
    ~AddUserWindow();

private:
    Ui::AddUserWindow *ui;
    QString name;
    QString surname;
    gender g;
};

#endif // ADDUSERWINDOW_H
