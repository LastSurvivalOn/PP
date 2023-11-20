#include "plaster.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPainterPath>
#include <QLabel>
#include <iostream>
Plaster::Plaster():QMainWindow()
{
    this->setWindowTitle("Новий");
    this->setGeometry(100, 100, 800, 600);
    image = new QImage(800, 600, QImage::Format_RGB32);
    image->fill(Qt::white);
    lastPoint = nullptr;
    drawing = false;
    brushsize = 5;
    brushColor = new QColor(Qt::black);
    painter = new QPainter(image);
    isnew=1;
    toolbar_a = new QToolBar(this);
    toolbar_a->setMovable(false);
    addToolBar(toolbar_a);

    instrument = new QComboBox();
    instrument->addItem("Олівець");
    instrument->addItem("Стирачка");
    //instrument->addItem("Заливка");
    instrument->addItem("Круг");
    instrument->addItem("Прямокутник");
    instrument->addItem("Заповнений круг");
    instrument->addItem("Заповнений прямокутник");
    QLabel *label = new QLabel("Інструмент: ", this);
    toolbar_a->addWidget(label);
    toolbar_a->addWidget(instrument);

    color = new QColorDialog(this);
    QAction *colorAction = new QAction("Змінити колір", this);
    connect(colorAction, &QAction::triggered, this, &Plaster::changeColorActionTriggered);
    toolbar_a->addAction(colorAction);

    width = new QSpinBox();
    width->setRange(1, 50);
    width->setValue(brushsize);
    toolbar_a->addWidget(width);

    //connect(shape, SIGNAL(currentIndexChanged(int)), this, SLOT(changeShape(int)));
    connect(instrument, SIGNAL(currentIndexChanged(int)), this, SLOT(changeInstrument(int)));
    connect(color, SIGNAL(colorSelected(const QColor&)), this, SLOT(changeColor(const QColor&)));
    connect(width, SIGNAL(valueChanged(int)), this, SLOT(changeWidth(int)));//BUG(???)
}

Plaster::Plaster(QImage *i, QString n):QMainWindow()
{
    this->setWindowTitle("Редагування");
    this->setGeometry(100, 100, 800, 600);
    this->image = i;
    lastPoint = nullptr;
    drawing = false;
    brushsize = 5; //BUG(???)
    brushColor = new QColor(Qt::black);
    painter = new QPainter(image);
    isnew=0;
    toolbar_a = new QToolBar(this);
    toolbar_a->setMovable(false);
    addToolBar(toolbar_a);
    this->n=n;
    instrument = new QComboBox();
    instrument->addItem("Олівець");
    instrument->addItem("Стирачка");
    //instrument->addItem("Заливка");
    instrument->addItem("Круг");
    instrument->addItem("Прямокутник");
    instrument->addItem("Заповнений круг");
    instrument->addItem("Заповнений прямокутник");
    toolbar_a->addWidget(instrument);

    color = new QColorDialog(this);
    QAction *colorAction = new QAction("Змінити колір", this);
    connect(colorAction, &QAction::triggered, this, &Plaster::changeColorActionTriggered);
    toolbar_a->addAction(colorAction);

    width = new QSpinBox();
    width->setRange(1, 50);
    width->setValue(brushsize);
    toolbar_a->addWidget(width);

    //connect(shape, SIGNAL(currentIndexChanged(int)), this, SLOT(changeShape(int)));
    //connect(instrument, SIGNAL(currentIndexChanged(int)), this, SLOT(changeInstrument(int)));
    //connect(color, SIGNAL(colorSelected(const QColor&)), this, SLOT(changeColor(const QColor&)));
    //connect(width, SIGNAL(valueChanged(int)), this, SLOT(changeWidth(int)));//BUG(???)
}

void Plaster::changeColorActionTriggered()
{
    QColor newColor = color->getColor(*brushColor, this, "Виберіть колір", QColorDialog::DontUseNativeDialog);
    if (newColor.isValid())
    {
        *brushColor = newColor;
    }
}

void Plaster::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        drawing = true;
        lastPoint = new QPoint(event->pos());
        painter->setPen(QPen(*brushColor, width->value(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

        int instrumentIndex = instrument->currentIndex();
        switch (instrumentIndex)
        {
        case 2: // Круг
            circleRect.setTopLeft(event->pos());
            circleRect.setBottomRight(event->pos());
            break;

        case 3: // Прямокутник
            rectangle.setTopLeft(event->pos());
            rectangle.setBottomRight(event->pos());
            break;

        case 4: // Круг зап
            circleRect.setTopLeft(event->pos());
            circleRect.setBottomRight(event->pos());
            break;

        case 5: // Прямокутник зап
            rectangle.setTopLeft(event->pos());
            rectangle.setBottomRight(event->pos());
            break;

        }
    }
}

void Plaster::mouseMoveEvent(QMouseEvent *event)
{
    if (drawing)
    {
        if (!lastPoint)
            return;
        int instrumentIndex = instrument->currentIndex();
        switch (instrumentIndex)
        {
        case 0:{
            painter->setPen(QPen(*brushColor, width->value(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter->drawLine(*lastPoint, event->pos());
            brushsize=width->value();
            break;}
        case 1:{
            painter->setPen(QPen(Qt::white, width->value(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter->drawLine(*lastPoint, event->pos());
            break;}
        /*case 2:{
            if (event->button() == Qt::LeftButton) {
                int x = event->x();
                int y = event->y();
                qDebug() << "Starting flood fill at" << x << y;
                floodFill(x, y, *brushColor);
            }
            break;}*/
        case 2: // Круг
            circleRect.setBottomRight(event->pos());
            break;
        case 3: // Прямокутник
            rectangle.setBottomRight(event->pos());
            break;
        case 4: // Круг з
            circleRect.setBottomRight(event->pos());
            break;
        case 5: // Прямокутник з
            rectangle.setBottomRight(event->pos());
            break;
        }

        delete lastPoint;
        lastPoint = new QPoint(event->pos());

        update();
    }
}

void Plaster::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing)
    {
        drawing = false;
        //painter->setBrush(QBrush(*brushColor, Qt::NoBrush));
        int instrumentIndex = instrument->currentIndex();
        switch (instrumentIndex)
        {
        case 2:
            painter->setBrush(QBrush(*brushColor, Qt::NoBrush));
            painter->drawEllipse(circleRect);
            break;
        case 3:
            painter->setBrush(QBrush(*brushColor, Qt::NoBrush));
            painter->drawRect(rectangle);
            break;
        case 4:
            painter->setBrush(QBrush(*brushColor, Qt::SolidPattern));
            painter->drawEllipse(circleRect);
            break;
        case 5:
            painter->setBrush(QBrush(*brushColor, Qt::SolidPattern));
            painter->drawRect(rectangle);
            break;
        }

        delete lastPoint;
        lastPoint = nullptr;
        update();
    }
}

void Plaster::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *image);
}

void Plaster::floodFill(int x, int y, QColor &newColor) {
    /*QColor colorhui = image->pixelColor(x, y);
    if(colorhui!=newColor){
        if(image->pixelColor(x-1, y)==colorhui){
            image->setPixelColor(x-1, y, newColor);
            floodFill(x-1, y, newColor, colorhui);
        }
        if(image->pixelColor(x+1, y)==colorhui){
            image->setPixelColor(x+1, y, newColor);
            floodFill(x+1, y, newColor, colorhui);
        }
        if(image->pixelColor(x, y+1)==colorhui){
            image->setPixelColor(x, y+1, newColor);
            floodFill(x, y+1, newColor, colorhui);
        }
        if(image->pixelColor(x, y-1)==colorhui){
            image->setPixelColor(x, y-1, newColor);
            floodFill(x, y-1, newColor, colorhui);
        }
    }*/
    qDebug() << "Flood Fill called at" << x << y;
    QColor oldColor = image->pixelColor(x, y);
    if (oldColor == newColor || !image->rect().contains(x, y)) {
        return;
    }

    floodFill(x, y, oldColor, newColor);
    update();
}

/*void Plaster::floodFill(int x, int y, QColor &newColor, QColor &colorhui) {
        if(image->pixelColor(x-1, y)==colorhui){
            image->setPixelColor(x-1, y, newColor);
            floodFill(x-1, y, newColor, colorhui);
        }
        if(image->pixelColor(x+1, y)==colorhui){
            image->setPixelColor(x+1, y, newColor);
            floodFill(x+1, y, newColor, colorhui);
        }
        if(image->pixelColor(x, y+1)==colorhui){
            image->setPixelColor(x, y+1, newColor);
            floodFill(x, y+1, newColor, colorhui);
        }
        if(image->pixelColor(x, y-1)==colorhui){
            image->setPixelColor(x, y-1, newColor);
            floodFill(x, y-1, newColor, colorhui);
        }*/
void Plaster::floodFill(int x, int y, QColor &oldColor, QColor &newColor) {
    if (!image->rect().contains(x, y) || image->pixelColor(x, y) != oldColor) {
        return;
    }

    image->setPixelColor(x, y, newColor);

    floodFill(x + 1, y, oldColor, newColor);
    floodFill(x - 1, y, oldColor, newColor);
    floodFill(x, y + 1, oldColor, newColor);
    floodFill(x, y - 1, oldColor, newColor);
}

void Plaster::closeEvent(QCloseEvent *event) {
    if(isnew){
        Save *s = new Save;
        s->show();
        //if(s->get_a()==1)
        //this->image->save(s->get()+".png");
        int result = s->exec();

        if (result == QDialog::Accepted) {
            this->image->save(s->get() + ".png");
        }

        // Make sure to delete the Save dialog to prevent memory leaks
        delete s;
    }
    else{
        qDebug() << "Saving image to existing file: " << this->n.toStdString();
        image->save(this->n);
    }
    QMainWindow::closeEvent(event);
}



