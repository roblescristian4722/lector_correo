#ifndef ELIMINAR_PROPIETARIO_H
#define ELIMINAR_PROPIETARIO_H

#include <QDialog>
#include <QMessageBox>
#include "lectorcorreo.h"

namespace Ui {
class eliminar_propietario;
}

class eliminar_propietario : public QDialog
{
    Q_OBJECT

public:
    explicit eliminar_propietario(LectorCorreo* lector, QWidget *parent = nullptr);
    ~eliminar_propietario();

private slots:
    void on_eliminarPB_clicked();

private:
    Ui::eliminar_propietario *ui;
    LectorCorreo* m_lector;
};

#endif // ELIMINAR_PROPIETARIO_H
