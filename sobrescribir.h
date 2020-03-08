#ifndef SOBRESCRIBIR_H
#define SOBRESCRIBIR_H

#include <QDialog>
#include "correo.h"
#include "ldl.h"
#include "lectorcorreo.h"

namespace Ui {
class Sobrescribir;
}

class Sobrescribir : public QDialog
{
    Q_OBJECT

public:
    explicit Sobrescribir(LectorCorreo* lector, Correo* actual, Correo* copia, int index, QWidget *parent = nullptr);
    ~Sobrescribir();

private slots:
    void on_actualPB_clicked();

    void on_copiaPB_clicked();

private:
    Ui::Sobrescribir *ui;
    Correo* m_copia;
    Correo* m_actual;
    LectorCorreo* m_lector;
    int m_index;
};

#endif // SOBRESCRIBIR_H
