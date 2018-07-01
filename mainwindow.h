#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qpyramidview.h"
#include <QScrollArea>

class QAction;
class QLabel;
class QMenu;
class QPixmap;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setFromCommandLine(QString file, double coeff);

private slots:
    void open(bool isFromCommandLine = false);
    void chooseFile();
    void chooseLayer();
    void setCoeff();

private:
    Ui::MainWindow *ui;
    QScrollArea* q;
    int currentFileIndex;
    double startCoeff = 0;
    QString currentFile = "";
    QLabel *imageLabel;
    QList<QPyramidView*> pyramidFiles;
    QMenu* fileMenu;
    QAction *openAct;
    QString fileName;
    void sortFiles();
    void createAction();
    void createMenu();
    void loadImage();
};

#endif // MAINWINDOW_H
