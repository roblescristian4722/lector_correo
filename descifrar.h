#ifndef DESCIFRAR_H
#define DESCIFRAR_H

#include <QDialog>
#include <QMessageBox>
#include <iostream>
#include <thread>
#include <fstream>
using namespace std;

namespace Ui {
class Descifrar;
}

class Descifrar : public QDialog
{
    Q_OBJECT

public:
    explicit Descifrar(QWidget *parent = nullptr);
    ~Descifrar();

private slots:
    void on_descifrarPB_clicked();
    void activar();
    void on_nombreLE_textChanged(const QString &arg1);
    void on_contraseniaLE_textChanged(const QString &arg1);

private:
    Ui::Descifrar *ui;
};

#endif // DESCIFRAR_H
