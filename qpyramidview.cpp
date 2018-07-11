#include "qpyramidview.h"
#include <QtMath>
#include <QPixmap>

QPyramidView::QPyramidView(QString fileName, QWidget * parent): QWidget(parent){
    this->fileName = fileName;
    QPixmap someFile(fileName);
    fileSize = someFile.size();
    pseudoDiagonal = qSqrt(qreal((fileSize.height() * fileSize.height()) + (fileSize.width() * fileSize.width())));
    calculateLayersSize();
}

// Вычисление нужных размеров для слоев
void QPyramidView::calculateLayersSize(){
    pyramidLayers.clear();
    int height = fileSize.height();
    int width = fileSize.width();
    pyramidLayers.push_back(QSize(width, height));
    while (true){
        height /= pyramidCoefficient;
        width /= pyramidCoefficient;
        if(height < 1 || width < 1) break;
        pyramidLayers.push_back(QSize(width, height));
    }
}

int QPyramidView::getPseudoDiagonal() const{
    return pseudoDiagonal;
}

QString QPyramidView::getFileName() const{
    return fileName;
}

int QPyramidView::getNumberOfLayers() const{
    return pyramidLayers.size();
}

double QPyramidView::getPyramidCoefficient() const{
    return pyramidCoefficient;
}

QSize QPyramidView::getLayerSize(const int& layerNumber) const{
    return pyramidLayers[layerNumber];
}

QSize QPyramidView::getFileSize() const{
    return fileSize;
}

void QPyramidView::setNewPyramidCoefficient(const double& newCoefficient){
    pyramidCoefficient = newCoefficient;
    calculateLayersSize();
}
