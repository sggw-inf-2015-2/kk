#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>

namespace Ui {
class UserWindow;
}

class UserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = 0);
    ~UserWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UserWindow *ui;
    int counter;
};

#endif // USERWINDOW_H
