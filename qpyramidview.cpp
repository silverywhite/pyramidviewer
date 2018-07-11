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
