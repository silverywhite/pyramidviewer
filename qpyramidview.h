#ifndef QPYRAMIDVIEW_H
#define QPYRAMIDVIEW_H

#include <QWidget>
#include <QVector>

class QPyramidView : public QWidget {
    friend class MainWindow;

    Q_OBJECT

public:
    QPyramidView(QString fileName, QWidget *parent = 0);

private:
    QVector<QSize> pyramidLayers;
    QString fileName;
    QSize fileSize;
    int pseudoDiagonal;
    double pyramidCoefficient = 2;
    void getFileSize();
    void setLayersSize();
};

#endif // QPYRAMIDVIEW_H
