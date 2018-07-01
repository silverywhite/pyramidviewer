#ifndef QPYRAMIDVIEW_H
#define QPYRAMIDVIEW_H

#include <QWidget>
#include <QVector>

class QPyramidView : public QWidget {
    friend class MainWindow;

    Q_OBJECT

public:
    QPyramidView(QString fileName, QWidget * parent = 0);
    ~QPyramidView();

private:
    QVector<QSize> pyramidLayers;
    QString fileName;
    QSize fileSize;
    int pseudoDiag;
    double pyramidCoeff = 2;
    void setFileSize();
    void setLayers();

};

#endif // QPYRAMIDVIEW_H
