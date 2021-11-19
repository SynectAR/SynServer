#include "mainwindow.h"
#include <QIcon>
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.resize(1200, 1200);
    w.setWindowTitle("Image uploader");
    w.setToolTip("Widget");
    //w.setWindowIcon(QIcon(""));
    w.show();
    return a.exec();
}
