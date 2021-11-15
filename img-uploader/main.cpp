#include "mainwindow.h"
#include <QIcon>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Image uploader");
    w.setToolTip("Widget");
    w.setWindowIcon(QIcon("icon.png"));
    w.show();
    return a.exec();
}
