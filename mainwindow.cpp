#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QStringList col;
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(6);
    col << "ID" << "De:" << "Para:" << "Asunto" << "Fecha" << "Hora";
    ui->tableWidget->setHorizontalHeaderLabels(col);
    Correo *tmp = new Correo;
    for (size_t i = 0; i < 10; i++)
    {
        if (m_lector.getPosicion(i))
        {
            *tmp = m_lector.leer(i + 1);
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            int fila = ui->tableWidget->rowCount() - 1;
            ui->tableWidget->setItem(fila, COL_ID,
                                     new QTableWidgetItem(QString::number(tmp->getIdentificador())));
            ui->tableWidget->setItem(fila, COL_REM,
                                     new QTableWidgetItem(tmp->getRem()));
            ui->tableWidget->setItem(fila, COL_DES,
                                     new QTableWidgetItem(tmp->getDestinatario()));
            ui->tableWidget->setItem(fila, COL_ASUNTO,
                                     new QTableWidgetItem(tmp->getAsunto()));
            ui->tableWidget->setItem(fila, COL_FECHA,
                                     new QTableWidgetItem(tmp->getFechaEnvio()));
            ui->tableWidget->setItem(fila, COL_HORA,
                                     new QTableWidgetItem(tmp->getHoraEnvio()));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_agregar_clicked()
{
    Correo *tmp = new Correo;
    bool *escribir = new bool(false);
    agregar a(tmp, escribir);
    a.setModal(true);
    a.exec();
    if (*escribir)
    {
        m_lector.crear(tmp, tmp->getIdentificador());
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int fila = ui->tableWidget->rowCount() - 1;
        ui->tableWidget->setItem(fila, COL_ID,
                                 new QTableWidgetItem(QString::number(tmp->getIdentificador())));
        ui->tableWidget->setItem(fila, COL_REM,
                                 new QTableWidgetItem(tmp->getRem()));
        ui->tableWidget->setItem(fila, COL_DES,
                                 new QTableWidgetItem(tmp->getDestinatario()));
        ui->tableWidget->setItem(fila, COL_ASUNTO,
                                 new QTableWidgetItem(tmp->getAsunto()));
        ui->tableWidget->setItem(fila, COL_FECHA,
                                 new QTableWidgetItem(tmp->getFechaEnvio()));
        ui->tableWidget->setItem(fila, COL_HORA,
                                 new QTableWidgetItem(tmp->getHoraEnvio()));
        delete tmp;
    }
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    qDebug() << row << " " << column << endl;
    m_row = row;
    m_column = column;
}

void MainWindow::on_eliminar_clicked()
{
    //ui->tableWidget->removeRow(m_row);
}
