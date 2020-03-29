#ifndef ELIMINAR_COPIA_H
#define ELIMINAR_COPIA_H

#include <QDialog>
#include <QMessageBox>
#include "lectorcorreo.h"
#include "parser.h"
#include "lsl.h"

namespace Ui {
class eliminar_copia;
}

class eliminar_copia : public QDialog
{
    Q_OBJECT

public:
    explicit eliminar_copia(LectorCorreo* lector, QWidget *parent = nullptr);
    ~eliminar_copia();

private slots:
    void on_eliminarPB_clicked();

private:
    Ui::eliminar_copia *ui;
    LectorCorreo* m_lector;
};

#endif // ELIMINAR_COPIA_H
