#include "qpyramidview.h"
#include <QtMath>

class QPixmap;

QPyramidView::QPyramidView(QString fileName, QWidget * parent): QWidget(parent){
    this->fileName = fileName;
    setFileSize();
    setLayers();
}

QPyramidView::~QPyramidView(){}

void QPyramidView::setFileSize(){
    QPixmap someFile(fileName);
    fileSize = someFile.size();
    pseudoDiag = qSqrt(qreal((fileSize.height() * fileSize.height()) + (fileSize.width() * fileSize.width())));
}

// Вычисление нужных размеров для слоев
void QPyramidView::setLayers(){
    pyramidLayers.clear();
    int height = fileSize.height();
    int width = fileSize.width();
    pyramidLayers.push_back(QSize(width, height));
    while (true){
        height /= pyramidCoeff;
        width /= pyramidCoeff;
        if(height < 1 || width < 1) break;
        pyramidLayers.push_back(QSize(width, height));
    }
}
