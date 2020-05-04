#ifndef AGREGAR_H
#define AGREGAR_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <ctime>
#include "lectorcorreo.h"

namespace Ui {
class agregar;
}

class agregar : public QDialog
{
    Q_OBJECT

public:
    explicit agregar(LectorCorreo* lector, bool hash = false,
                     QWidget *parent = nullptr);
    ~agregar();

private slots:
    void on_guardar_clicked();

private:
    Ui::agregar *ui;

    // Puntero utilizado para acceder al
    // lector principal y métodos de creación de archivos
    LectorCorreo* m_lector;
    bool m_hash;
};

#endif // AGREGAR_H
