#include "save.h"
#include "ui_save.h"

Save::Save(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Save),
    name("new")
{
    ui->setupUi(this);
    this->setWindowTitle("Введіть назву файлу");
    //this->is_acc=0;
}

Save::~Save()
{
    delete ui;
}

void Save::on_buttonBox_accepted()
{
    this->name = this->ui->lineEdit->text();
    //this->is_acc=0;
    this->hide();
}


void Save::on_buttonBox_rejected()
{
    this->hide();
}

QString Save::get(){
    return this->name;
}

/*bool Save::get_a(){
    return this->is_acc;
}*/
