#ifndef QPYRAMIDVIEW_H
#define QPYRAMIDVIEW_H

#include <QWidget>

class QPyramidView : public QWidget
{
    Q_OBJECT

public:
    QPyramidView(QString fileName);
    QString fileName;

private:

};

#endif // QPYRAMIDVIEW_H
