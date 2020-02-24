#ifndef MODIFICAR_COPIA_H
#define MODIFICAR_COPIA_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include "correo.h"
#include "lectorcorreo.h"
#include "parser.h"

namespace Ui {
class modificar_copia;
}

class modificar_copia : public QDialog
{
    Q_OBJECT

public:
    explicit modificar_copia(LectorCorreo* lector, QWidget *parent = nullptr);
    ~modificar_copia();

private slots:

    void on_guardar_2_clicked();

private:
    Ui::modificar_copia *ui;
    LectorCorreo* m_lector;
};

#endif // MODIFICAR_COPIA_H
