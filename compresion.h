#ifndef COMPRESION_H
#define COMPRESION_H

#include <QDialog>
#include <QMessageBox>
#include <iostream>
#include <thread>
using namespace std;

void th_func(string command);

namespace Ui {
class compresion;
}

class compresion : public QDialog
{
    Q_OBJECT

public:
    explicit compresion(QString action, QWidget *parent = nullptr);
    ~compresion();

private slots:
    void on_accionPB_clicked();

private:
    Ui::compresion *ui;
};

#endif // COMPRESION_H
