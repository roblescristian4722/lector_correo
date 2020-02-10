#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include "string.h"
#include "agregar.h"
#include "vistaprevia.h"
#include "modificar.h"
#include "agregar.h"
#include "correo.h"
#include "lectorcorreo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_agregar_clicked();

    void on_eliminar_clicked();

    void on_modificar_clicked();

    void on_mostrarTodo_clicked();

    void on_bandejaTabla_cellClicked(int row, int column);

    void on_idBuscarPB_clicked();

    void on_remBuscarPB_clicked();

    void on_bandejaTabla_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;

    /*
     * Objeto lector que se encargará de administrar
     * todos los datos de la interfaz
    */
    LectorCorreo m_lector;
    /*
     * Correo temporal que guardará la información de cada
     * correo obtenido al buscar con un ID
    */

    LDL<Correo> m_lista;
    unsigned long m_fila;

    enum COLUMNAS
    {
        COL_ID,
        COL_REM,
        COL_DES,
        COL_ASUNTO,
        COL_CC,
        COL_CCC,
        COL_FECHA,
        COL_HORA
    };
};
#endif // MAINWINDOW_H
