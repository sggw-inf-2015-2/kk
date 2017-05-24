#include "userwindow.h"
#include "ui_userwindow.h"
#include <QDesktopWidget>

UserWindow::UserWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWindow)
{    
    ui->setupUi(this);
    QDesktopWidget *desktop = QApplication::desktop();
    QRect rect = desktop->screenGeometry(1);
    move(rect.topLeft());
    this->showMaximized();
}

UserWindow::~UserWindow()
{
    delete ui;
}
