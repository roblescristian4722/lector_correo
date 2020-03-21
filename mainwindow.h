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
#include "avl_tree.h"

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

private:
    Ui::MainWindow *ui;

    AVLTree<LectorCorreo::Indice> m_indices;

    /*
     * Objeto lector que se encargará de administrar
     * todos los datos de la interfaz
    */
    LectorCorreo *m_lector;

    unsigned int m_fila;
    LDL<unsigned int> m_ids;

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
};
#endif // MAINWINDOW_H
