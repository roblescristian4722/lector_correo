#ifndef CIFRAR_H
#define CIFRAR_H

#include <QDialog>
#include <QMessageBox>
#include <iostream>
#include <thread>
#include <fstream>
using namespace std;

namespace Ui {
class Cifrar;
}

class Cifrar : public QDialog
{
    Q_OBJECT

public:
    explicit Cifrar(QWidget *parent = nullptr);
    ~Cifrar();


private slots:
    void on_contrasenaCB_stateChanged(int arg1);
    void on_archivoDestinoLE_textChanged(const QString &arg1);
    void on_contrasenaLE_textChanged(const QString &arg1);
    void on_cifrarPB_clicked();
    void activar();

private:
    Ui::Cifrar *ui;
    bool m_personalizada;
};

#endif // CIFRAR_H
