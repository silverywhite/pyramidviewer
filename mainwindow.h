#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qpyramidview.h"
#include <QScrollArea>
#include <QAction>
#include <QLabel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setFromCommandLine(const QString& file, const double& coeff);

private slots:
    void open(const bool& isFromCommandLine = false);
    void setCoefficient();
    void chooseFile();
    void chooseLayer();

private:
    Ui::MainWindow *ui;
    int currentFileIndex;
    double startCoefficient = 0;
    QScrollArea *q;
    QString currentFile = "";
    QLabel *imageLabel;
    QList<QPyramidView*> pyramidFiles;
    QMenu *fileMenu;
    QAction *openAct;
    QString fileName;
    void sortFiles();
    void createAction();
    void createMenu();
    void loadImage() const;
};

#endif // MAINWINDOW_H
