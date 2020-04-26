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
#include "parser.h"
#include "sobrescribir.h"
#include "modificar_copia.h"
#include "eliminar_copia.h"
#include "eliminar_propietario.h"
#include "modificar_propietario.h"
#include "avl_tree_primario.h"
#include "hash_map.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void crearFila(Correo& correo);
    int busqueda_binaria(int dato);
    int busqueda_binaria(Vector<Correo> &vec, QString dato);
    void shell_sort(size_t n, Vector<Correo> &vec);
    void shell_sort();
    void limpiarFilas();

private slots:
    void on_agregar_clicked();
    void on_eliminar_clicked();
    void on_modificar_clicked();
    void on_mostrarTodo_clicked();
    void on_bandejaTabla_cellClicked(int row, int column);
    void on_buscarPB_clicked();
    void on_bandejaTabla_cellDoubleClicked(int row, int column);
    void on_actionRecuperar_copia_de_seguridad_triggered();
    void on_actionCrear_copia_de_seguridad_triggered();
    void on_actionModificar_correo_en_copia_de_seguridad_triggered();
    void on_actionEliminar_correo_en_copia_de_seguridad_triggered();
    void on_actionExportar_copia_de_propietario_triggered();
    void on_actionEliminar_correo_triggered();
    void on_actionModificar_Correo_triggered();
    void on_opcCB_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    AVLTreePrimario m_indices;
    AVLTreePrimario m_paginados;
    AVLTreeSecundario m_rem;
    AVLTreeSecundario m_des;
    HashMap<string, LSL<IndicePrimario>*> m_mapRem;
    HashMap<string, LSL<IndicePrimario>*> m_mapDes;

    // Objeto lector que se encargará de administrar
    // todos los datos de la interfaz
    LectorCorreo *m_lector;

    int m_fila;
    LSL<long> m_ids;

    enum COLUMNAS
    {
        COL_ID,
        COL_FECHA,
        COL_HORA,
        COL_REM,
        COL_DES,
        COL_CC,
        COL_CCC,
        COL_ASUNTO
    };

    enum OPC_BUS
    {
        OPC_ID = 0,
        OPC_REM,
        OPC_REM_RAM,
        OPC_IND_PRIM,
        OPC_IND_SEC_REM,
        OPC_IND_SEC_DES,
        OPC_IND_PAGINADOS,
        OPC_HASH_REM,
        OPC_HASH_DES
    };
};
#endif // MAINWINDOW_H
