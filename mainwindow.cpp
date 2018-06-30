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
    q->setFixedSize(550,550);
    q->setWidgetResizable(true);
    q->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    q->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    loadImage();
    q->setWidget(imageLabel);
    ui->verticalLayout->addWidget(q);

    connect(ui->fileComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseFile()));
    connect(ui->layerComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseLayer()));

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
        QPyramidView *someImg = new QPyramidView(fileName);
        pyramidFiles.append(someImg);
        currentFile = fileName;
        ui->fileComboBox->addItem(fileName);
        ui->fileComboBox->setCurrentText(fileName);
        loadImage();
    }
}

// Происходит при выборе файла
void MainWindow::chooseFile()
{
    disconnect(ui->layerComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseLayer()));
    ui->layerComboBox->clear();
    connect(ui->layerComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseLayer()));
    int i;
    QString key = ui->fileComboBox->currentText();
    for (currentFileIndex = 0; currentFileIndex < pyramidFiles.size(); currentFileIndex++){
        if(pyramidFiles[currentFileIndex]->fileName == key){
            break;
        }
    }
    for (i = 0; i < pyramidFiles[currentFileIndex]->pyramidLayers.size(); i++){
        ui->layerComboBox->addItem(QString::number(i));
    }
    currentFile = pyramidFiles[currentFileIndex]->fileName;
    loadImage();
}

// Происходит при выборе слоя
void MainWindow::chooseLayer()
{
    QPixmap img(currentFile);
    int layerNumber = ui->layerComboBox->currentIndex();
    QSize originalSize = pyramidFiles[currentFileIndex]->fileSize;
    QSize newSize = pyramidFiles[currentFileIndex]->pyramidLayers[layerNumber];
    ui->actualSize->clear();
    QString actualSize = QString::number(newSize.width()) + 'x' + QString::number(newSize.height());
    ui->actualSize->setText(actualSize);
    img = img.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    img = img.scaled(originalSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(img);
    q->update();
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

