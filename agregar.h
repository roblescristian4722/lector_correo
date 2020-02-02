#ifndef AGREGAR_H
#define AGREGAR_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <ctime>
#include "correo.h"
#include "lectorcorreo.h"

namespace Ui {
class agregar;
}

class agregar : public QDialog
{
    Q_OBJECT

public:
    explicit agregar(Correo* correo, bool* escribir, bool* pos, QWidget *parent = nullptr);
    ~agregar();

private slots:
    void on_guardar_clicked();

private:
    Ui::agregar *ui;
    Correo* m_correo;
    bool* m_pos;
    bool* m_escribir;
};

#endif // AGREGAR_H
