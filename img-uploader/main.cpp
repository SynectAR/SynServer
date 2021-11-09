#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    //QLabel *label = new QLabel("Hello");
    //label -> resize(400, 400);
    //label -> show();


    MainWindow w;
    w.show();
    return app.exec();
}

//запускаем все приложение и показываем его пользователю
