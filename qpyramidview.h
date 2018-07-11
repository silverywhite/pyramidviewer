#ifndef QPYRAMIDVIEW_H
#define QPYRAMIDVIEW_H

#include <QWidget>
#include <QVector>

class QPyramidView : public QWidget {

    Q_OBJECT

public:
    QPyramidView(QString fileName, QWidget *parent = 0);
    int getPseudoDiagonal() const;
    int getNumberOfLayers() const;
    double getPyramidCoefficient() const;
    QSize getLayerSize(const int& layerNumber) const;
    QString getFileName() const;
    QSize getFileSize() const;
    void setNewPyramidCoefficient(const double& newCoefficient);

private:
    QVector<QSize> pyramidLayers;
    QString fileName;
    QSize fileSize;
    int pseudoDiagonal;
    double pyramidCoefficient = 2;
    void calculateLayersSize();
};

#endif // QPYRAMIDVIEW_H
