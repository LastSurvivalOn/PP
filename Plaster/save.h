#ifndef SAVE_H
#define SAVE_H
#include <QString>
#include <QDialog>

namespace Ui {
class Save;
}

class Save : public QDialog
{
    Q_OBJECT

public:
    explicit Save(QWidget *parent = nullptr);
    ~Save();
        QString get();
    //bool get_a();
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
private:
    Ui::Save *ui;
    QString name;
    //bool is_acc;
};

#endif // SAVE_H
