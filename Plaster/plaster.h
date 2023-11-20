#ifndef PLASTER_H
#define PLASTER_H
#include <QMainWindow>
#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QBrush>
#include <QPainter>
#include <QToolBar>
#include <QAction>
#include <QComboBox>
#include <QColorDialog>
#include <QSpinBox>
#include "save.h"
class Plaster: public QMainWindow {
    Q_OBJECT
public:
    Plaster();
    Plaster(QImage *i, QString n);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void changeColorActionTriggered();
    void changeWidth(int newWidth);
    Plaster(const Plaster& h){
        this->image=h.image;
        this->drawing=h.drawing;
        this->lastPoint=h.lastPoint;
        this->brushsize=h.brushsize;
        this->brushColor=h.brushColor;
        this->toolbar_a=h.toolbar_a;
        //this->shape=h.shape;
        this->instrument=h.instrument;
        this->color=h.color;
        this->width=h.width;
        this->circleRect=h.circleRect;
        this->rectangle=h.rectangle;
        this->s=h.s;
        this->isnew=h.isnew;
        this->n=h.n;
    }
    void closeEvent(QCloseEvent *event);
private:
    bool isnew;
    QImage *image;
    bool drawing;
    QPoint *lastPoint;
    int brushsize;
    QColor *brushColor;
    Save*s;
    QToolBar *toolbar_a;
    //QComboBox *shape;
    QComboBox *instrument;
    QColorDialog *color;
    QSpinBox *width;

    QPainter *painter;
    void floodFill(int x, int y, QColor &newColor);
    void floodFill(int x, int y, QColor &newColor, QColor &colorhui);
    QString n;
    QRect circleRect;
    QRect rectangle;
};

#endif // PLASTER_H
