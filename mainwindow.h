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

private slots:
    void open();

private:
    Ui::MainWindow *ui;
    QScrollArea* q;
    QString currentFile = "";
    QLabel *imageLabel;
    QPyramidView *someImg;
    QMenu* fileMenu;
    QAction *openAct;
    QString fileName;
    void createAction();
    void createMenu();
    void loadImage();
};

#endif // MAINWINDOW_H
