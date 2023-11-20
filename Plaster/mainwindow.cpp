#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    pl(nullptr)
{
    ui->setupUi(this);
    QString imagePath = "back.png";
    QPixmap backgroundImage(imagePath);
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(backgroundImage));
    this->setPalette(palette);
    this->setFixedSize(920, 651);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Виберіть зображення"), "", tr("Зображення (*.png *.jpg *.bmp)"));

    if (!filePath.isEmpty()) {
        QImage *loadedImage = new QImage(filePath);
        if (loadedImage->isNull()) {
            qDebug() << "не завантажено";
        } else {
            Plaster *p = new Plaster(loadedImage, filePath);
            this->pl=p;
            pl->show();
        }
    }
}


void MainWindow::on_action_2_triggered()
{
    Plaster *p = new Plaster();
    this->pl=p;
    pl->show();
}

