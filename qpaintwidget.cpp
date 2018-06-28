#include "qpaintwidget.h"

#include <QPainter>
#include <QPixmap>

QPaintWidget::QPaintWidget(QWidget * parent) : QWidget(parent)
{
}

void QPaintWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    QPixmap img(500,500);
    QColor white(255,255,255);
    img.fill(white);
    p.drawPixmap(0,0,img);
    this->move(40,60);
}
