#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QScrollArea>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageLabel = new QLabel;
    imageLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    q = new QScrollArea(this);
    loadImage();
    q->setFixedSize(550,550);
    q->setWidget(imageLabel);
    q->setWidgetResizable(true);
    q->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    q->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->verticalLayout->addWidget(q);
    createAction();
    createMenu();
}

MainWindow::~MainWindow()
{
    q->deleteLater();
    delete ui;
}

void MainWindow::open()
{
    fileName = QFileDialog::getOpenFileName(0, "Open File", "", "*.png *.jpg");
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        someImg = new QPyramidView(fileName);
        currentFile = fileName;
        loadImage();
    }
}

void MainWindow::createAction()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
}


void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
}

void MainWindow::loadImage() {
    QPixmap img(500,500);
    if(currentFile == ""){
        QColor white(255,255,255);
        img.fill(white);
    }
    else {
        img.load(currentFile);
    }
    imageLabel->setPixmap(img);
    q->update();
}
