#ifndef QPYRAMIDVIEW_H
#define QPYRAMIDVIEW_H

#include <QWidget>

class QPyramidView : public QWidget
{
    Q_OBJECT

public:
    QPyramidView(QString fileName, QWidget * parent = 0);
    QString fileName;
    ~QPyramidView();

private:
    QSize fileSize;
    void setFileSize();

};

#endif // QPYRAMIDVIEW_H
