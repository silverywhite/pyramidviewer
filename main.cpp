#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(QSize(650,650));
    w.setWindowTitle("Pyramid Viewer");
    if(argc >= 3){
        w.setFromCommandLine(QString(argv[1]), atof(argv[2]));
    }
    w.show();

    return a.exec();
}
