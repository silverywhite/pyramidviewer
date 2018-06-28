#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(QSize(600,600));
    w.setWindowTitle("Pyramid Viewer");
    w.show();

    return a.exec();
}
