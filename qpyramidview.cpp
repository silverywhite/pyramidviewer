#include "qpyramidview.h"

class QPixmap;

QPyramidView::QPyramidView(QString fileName, QWidget * parent): QWidget(parent)
{
    this->fileName = fileName;
}

QPyramidView::~QPyramidView()
{
}

void QPyramidView::setFileSize()
{
    QPixmap someFile(fileName);
    fileSize = someFile.size();
}

