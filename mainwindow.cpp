#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QStringList col;
    Correo *tmp = new Correo;

    // Se inicializa la interfaz y todos sus atributos
    ui->setupUi(this);

    // Se escoge el nombre para la ventana principal
    this->setWindowTitle("Yi Mail");

    // Se especifica la cantidad de columas que tendrá la tabla
    // Para luego insgresar los nombres de cada una
    ui->tableWidget->setColumnCount(8);
    col << "ID" << "De:" << "Para:" << "Asunto" << "CC" << "CC Ciega" << "Fecha" << "Hora" ;
    ui->tableWidget->setHorizontalHeaderLabels(col);

    // Dentro de este ciclo se recuperará cada uno de los datos
    // del archivo binario previamente realizado y se añadiran
    // de uno en uno a la tabla
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
            ui->tableWidget->setItem(fila, COL_CC,
                                     new QTableWidgetItem(tmp->getCopiaCarbon()));
            ui->tableWidget->setItem(fila, COL_CCC,
                                     new QTableWidgetItem(tmp->getCopiaCarbonCiega()));
            ui->tableWidget->setItem(fila, COL_FECHA,
                                     new QTableWidgetItem(tmp->getFechaEnvio()));
            ui->tableWidget->setItem(fila, COL_HORA,
                                     new QTableWidgetItem(tmp->getHoraEnvio()));
        }
    }
    delete tmp;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_agregar_clicked()
{
    Correo *tmp = new Correo;
    bool *escribir = new bool(false);
    agregar a(tmp, escribir, m_lector.getPosicion());
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
        ui->tableWidget->setItem(fila, COL_CC,
                                 new QTableWidgetItem(tmp->getCopiaCarbon()));
        ui->tableWidget->setItem(fila, COL_CCC,
                                 new QTableWidgetItem(tmp->getCopiaCarbonCiega()));
        ui->tableWidget->setItem(fila, COL_FECHA,
                                 new QTableWidgetItem(tmp->getFechaEnvio()));
        ui->tableWidget->setItem(fila, COL_HORA,
                                 new QTableWidgetItem(tmp->getHoraEnvio()));
        delete tmp;
        delete escribir;
    }
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    m_row = row;
    m_column = column;
}

void MainWindow::on_eliminar_clicked()
{
    // Aún sin implementar
}

void MainWindow::on_modificar_clicked()
{
    if (!ui->tableWidget->rowCount())
        QMessageBox::warning(this, "Bandeja vacía", "Aún no hay correos. Intente agregar uno primero");
    else
    {
        Correo *tmp = new Correo;
        bool *escribir = new bool(false);
        modificar* a;
        size_t id = size_t(ui->tableWidget->item(m_row, COL_ID)->text().toInt());

        *tmp = m_lector.leer(id);
        a = new modificar(tmp, escribir, id);
        a->exec();

        if (*escribir)
        {
            m_lector.crear(tmp, tmp->getIdentificador());
            ui->tableWidget->setItem(m_row, COL_ID,
                                     new QTableWidgetItem(QString::number(tmp->getIdentificador())));
            ui->tableWidget->setItem(m_row, COL_REM,
                                     new QTableWidgetItem(tmp->getRem()));
            ui->tableWidget->setItem(m_row, COL_DES,
                                     new QTableWidgetItem(tmp->getDestinatario()));
            ui->tableWidget->setItem(m_row, COL_ASUNTO,
                                     new QTableWidgetItem(tmp->getAsunto()));
            ui->tableWidget->setItem(m_row, COL_CC,
                                     new QTableWidgetItem(tmp->getCopiaCarbon()));
            ui->tableWidget->setItem(m_row, COL_CCC,
                                     new QTableWidgetItem(tmp->getCopiaCarbonCiega()));
            ui->tableWidget->setItem(m_row, COL_FECHA,
                                     new QTableWidgetItem(tmp->getFechaEnvio()));
            ui->tableWidget->setItem(m_row, COL_HORA,
                                     new QTableWidgetItem(tmp->getHoraEnvio()));
            delete tmp;
            delete escribir;
        }
        delete a;
    }
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    Correo* correo = new Correo;
    *correo = m_lector.leer(row + 1);
    vistaprevia* v = new vistaprevia(correo);
    v->setModal(true);
    v->exec();
    delete v;
    delete correo;
}
