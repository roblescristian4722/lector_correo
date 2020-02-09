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
    explicit modificar(LDL<Correo>* lista, LectorCorreo* lector, unsigned long index, QWidget *parent = nullptr);
    ~modificar();

private slots:
    void on_guardar_clicked();

private:
    Ui::modificar *ui;

    /*
     * Correo temporal que se utiliza para enviar la
     * información modificada del correo a la ventana
     * principal
    */
    LDL<Correo>* m_lista;

    /*
     * Puntero utilizado para acceder al
     * lector principal y métodos de creación de archivos
    */
    LectorCorreo* m_lector;

    unsigned long m_index;
};

#endif // MODIFICAR_H
