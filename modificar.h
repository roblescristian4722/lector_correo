#ifndef MODIFICAR_H
#define MODIFICAR_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include "correo.h"
#include "lectorcorreo.h"

namespace Ui {
class modificar;
}

class modificar : public QDialog
{
    Q_OBJECT

public:
    explicit modificar(LectorCorreo* lector, long index, AVLTreePrimario* indicesMem, QWidget *parent = nullptr);
    ~modificar();

private slots:
    void on_guardar_clicked();

private:
    Ui::modificar *ui;

    /*
     * Puntero utilizado para acceder al
     * lector principal y métodos de creación de archivos
    */
    LectorCorreo* m_lector;
    Correo m_correoTmp;
    AVLTreePrimario* m_indicesMem;
    unsigned long m_index;
};

#endif // MODIFICAR_H
