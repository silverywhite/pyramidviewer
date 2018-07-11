#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QSignalBlocker>
#include <QScrollArea>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),  ui(new Ui::MainWindow){
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

    connect(ui->coeffButton, &QPushButton::clicked, this, setCoefficient);
    connect(ui->fileComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, chooseFile);
    connect(ui->layerComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, chooseLayer);

    createAction();
    createMenu();
}

MainWindow::~MainWindow(){
    q->deleteLater();
    delete ui;
}

void MainWindow::open(bool isFromCommandLine){
    if(!isFromCommandLine){
        fileName = QFileDialog::getOpenFileName(0, "Open File", "", "*.png *.jpg");
    }
    else if(isFromCommandLine){
        fileName = currentFile;
    }

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        QFileInfo fileinfo(file);

        if (!file.open(QIODevice::ReadOnly)){
            QMessageBox::information(this, "Unable to open file",
                file.errorString());
            return;
        }

        if (fileinfo.suffix() != "jpg" && fileinfo.suffix() != "png"){
            QMessageBox::information(this, "Unsupported file format",
                "Please, choose jpeg or png file");
            return;
        }

        QPyramidView *someImg = new QPyramidView(fileName);
        pyramidFiles.append(someImg);
        sortFiles();
        currentFile = fileName;
        ui->fileComboBox->setCurrentText(fileName);
        if(isFromCommandLine){
            ui->coeffSpinBox->setValue(startCoefficient);
            ui->coeffButton->click();
        }
        loadImage();
    }
}

// Сортировка файлов по возрастанию диагонали
void MainWindow::sortFiles(){
    int sortPlace = pyramidFiles.size()-1;

    while(sortPlace > 0 && (pyramidFiles[sortPlace]->pseudoDiagonal <= pyramidFiles[sortPlace-1]->pseudoDiagonal)){
        pyramidFiles.swap(sortPlace, sortPlace-1);
        sortPlace--;
    }

    QSignalBlocker fileComboBoxBlocker(ui->fileComboBox);
    ui->fileComboBox->clear();
    fileComboBoxBlocker.unblock();
    for (int j = 0; j < pyramidFiles.size(); j++){
        ui->fileComboBox->addItem(pyramidFiles[j]->fileName);
    }
}

// Происходит при выборе файла
void MainWindow::chooseFile(){
    QSignalBlocker layerComboBoxBlocker(ui->layerComboBox);
    ui->layerComboBox->clear();
    layerComboBoxBlocker.unblock();

    QString key = ui->fileComboBox->currentText();
    for (currentFileIndex = 0; currentFileIndex < pyramidFiles.size(); currentFileIndex++){
        if(pyramidFiles[currentFileIndex]->fileName == key){
            break;
        }
    }

    for (int i = 0; i < pyramidFiles[currentFileIndex]->pyramidLayers.size(); i++){
        ui->layerComboBox->addItem(QString::number(i));
    }
    currentFile = pyramidFiles[currentFileIndex]->fileName;
    ui->coeffSpinBox->setValue(pyramidFiles[currentFileIndex]->pyramidCoefficient);
    loadImage();
}

// Происходит при выборе слоя
void MainWindow::chooseLayer(){       
    int layerNumber = ui->layerComboBox->currentIndex();
    QSize newSize = pyramidFiles[currentFileIndex]->pyramidLayers[layerNumber];

    ui->actualSize->clear();
    QString actualSize = QString("%1x%2").arg(QString::number(newSize.width())).arg(QString::number(newSize.height()));
    ui->actualSize->setText(actualSize);

    if(currentFile != ""){
        QPixmap img(currentFile);
        QSize originalSize = pyramidFiles[currentFileIndex]->fileSize;
        img = img.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        img = img.scaled(originalSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        imageLabel->setPixmap(img);
        q->update();
    }
}

// Происходит, когда  нажимается кнопка задания коэффициента
void MainWindow::setCoefficient(){
    if(currentFile != ""){
        pyramidFiles[currentFileIndex]->pyramidCoefficient = ui->coeffSpinBox->value();
        pyramidFiles[currentFileIndex]->calculateLayersSize();
        QSignalBlocker layerComboBoxBlocker(ui->layerComboBox);
        ui->layerComboBox->clear();
        layerComboBoxBlocker.unblock();
        for (int i = 0; i < pyramidFiles[currentFileIndex]->pyramidLayers.size(); i++){
            ui->layerComboBox->addItem(QString::number(i));
        }
    }
}

void MainWindow::createAction(){
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
}

void MainWindow::createMenu(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
}

void MainWindow::loadImage(){
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

void MainWindow::setFromCommandLine(QString file, double coeff){
    if(!(file.contains("/"))){
        QMessageBox::warning(this, "Wrong command arguments", tr("Usage: PyramidViewer.exe -file- -coefficient-"));
    }

    this->startCoefficient = coeff;
    this->currentFile = file;
    open(true);
}
