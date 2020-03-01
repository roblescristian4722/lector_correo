#ifndef MODIFICAR_PROPIETARIO_H
#define MODIFICAR_PROPIETARIO_H

#include <QDialog>
#include <QMessageBox>
#include "correo.h"
#include "lectorcorreo.h"

namespace Ui {
class modificar_propietario;
}

class modificar_propietario : public QDialog
{
    Q_OBJECT

public:
    explicit modificar_propietario(LectorCorreo* lector, QWidget *parent = nullptr);
    ~modificar_propietario();

private slots:
    void on_guardar_2_clicked();

private:
    Ui::modificar_propietario *ui;
    LectorCorreo* m_lector;
};

#endif // MODIFICAR_PROPIETARIO_H
