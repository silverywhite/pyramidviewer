#include "qpyramidview.h"

class QPixmap;

QPyramidView::QPyramidView(QString fileName, QWidget * parent): QWidget(parent)
{
    this->fileName = fileName;
    setFileSize();
    setLayers();
}

QPyramidView::~QPyramidView()
{
}

void QPyramidView::setFileSize()
{
    QPixmap someFile(fileName);
    fileSize = someFile.size();
}

// Вычисление нужных размеров для слоев
void QPyramidView::setLayers()
{
    int height = fileSize.height();
    int width = fileSize.width();
    pyramidLayers.push_back(QSize(width, height));
    while (height > 1 && width > 1){
        height /= pyramidCoeff;
        width /= pyramidCoeff;
        pyramidLayers.push_back(QSize(width, height));
    }
}
