#ifndef MODIFICAR_H
#define MODIFICAR_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include "correo.h"

namespace Ui {
class modificar;
}

class modificar : public QDialog
{
    Q_OBJECT

public:
    explicit modificar(Correo* correo, bool* escribir, size_t id, QWidget *parent = nullptr);
    ~modificar();

private slots:
    void on_guardar_clicked();

private:
    Ui::modificar *ui;
    Correo* m_correo;
    bool* m_escribir;
    size_t m_id;
};

#endif // MODIFICAR_H
