#ifndef USERWINDOW_H
#define USERWINDOW_H

#include "user.h"
#include <QMainWindow>

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = 0);
    ~UserWindow();
    void resizeEvent(QResizeEvent *event) override;
    void InsertUserToRanking(User *user,int ID);
    void ClearRanking();

private:
    Ui::UserWindow *ui;
};

#endif // USERWINDOW_H
