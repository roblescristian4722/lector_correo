#ifndef SOBRESCRIBIR_H
#define SOBRESCRIBIR_H

#include <QDialog>
#include "correo.h"
#include "lectorcorreo.h"

namespace Ui {
class Sobrescribir;
}

class Sobrescribir : public QDialog
{
    Q_OBJECT

public:
    explicit Sobrescribir(LectorCorreo* lector, Correo* actual, Correo* copia,
                          AVLTreeSecundario* rem, AVLTreeSecundario* des, QWidget *parent = nullptr);
    ~Sobrescribir();

private slots:
    void on_actualPB_clicked();

    void on_copiaPB_clicked();

private:
    Ui::Sobrescribir *ui;
    Correo* m_copia;
    Correo* m_actual;
    LectorCorreo* m_lector;
    AVLTreeSecundario* m_rem;
    AVLTreeSecundario* m_des;
};

#endif // SOBRESCRIBIR_H
