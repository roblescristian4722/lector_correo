#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include "agregar.h"
#include "ldl.h"
#include "correo.h"
#include "lectorcorreo.h"
#include "agregar.h"

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

    void on_tableWidget_cellClicked(int row, int column);

    void on_eliminar_clicked();

private:
    Ui::MainWindow *ui;
    LectorCorreo m_lector;
    int m_row, m_column;
    enum COLUMNAS
    {
        COL_ID,
        COL_REM,
        COL_DES,
        COL_ASUNTO,
        COL_FECHA,
        COL_HORA
    };
};
#endif // MAINWINDOW_H
