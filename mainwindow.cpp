#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QStringList columnas;

    // Se inicializa la interfaz y todos sus atributos
    ui->setupUi(this);

    // Se escoge el nombre para la ventana principal
    this->setWindowTitle("Yi Mail");

    // Se inicializa la tabla
    ui->bandejaTabla->setColumnCount(8);
    columnas << "ID" << "Fecha de envío" << "Hora de envío"
             << "Remitente" << "Destinatario" << "CC" << "CCC"
             << "Asunto";
    ui->bandejaTabla->setHorizontalHeaderLabels(columnas);

    /*
     * Se recuperan los datos del archivo binario en la
     * lista doblemente ligada que forma parte de la clase
    */
    m_lector.leer(&m_lista);

    on_mostrarTodo_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_agregar_clicked()
{
    agregar a(&m_lector, &m_lista);
    a.setModal(true);
    a.exec();
    on_mostrarTodo_clicked();
}

void MainWindow::on_eliminar_clicked()
{
    unsigned long id;
    unsigned long idElim = 0;
    this->setCursor(Qt::WaitCursor);
    if (!ui->bandejaTabla->rowCount())
    {
        QMessageBox::warning(this, "Sin correo seleccionado",
                             "No hay correos seleccionados, intente buscar o añadir uno");
        return;
    }
    id = ui->bandejaTabla->item(m_fila, COL_ID)->text().toULong();
    for (idElim; idElim < m_lista.size(); idElim++)
        if (id == atol(m_lista[idElim].getIdentificador()))
            break;
    m_lista.erase(idElim);
    m_lector.eliminar(id);
    this->setCursor(Qt::ArrowCursor);
    on_mostrarTodo_clicked();
}

void MainWindow::on_modificar_clicked()
{
    Correo* mod = new Correo;
    unsigned long idMod = 0;
    unsigned long id;
    if (!ui->bandejaTabla->rowCount())
    {
        QMessageBox::warning(this, "Sin correo seleccionado",
                             "No hay correos seleccionados, intente buscar o añadir uno");
        return;
    }

    id = ui->bandejaTabla->item(m_fila, COL_ID)->text().toULong();

    for(idMod = 0; idMod < m_lista.size(); idMod++)
        if (atol(m_lista[idMod].getIdentificador()) == id)
            break;
    modificar m(&m_lista, &m_lector, idMod);
    m.exec();
    on_mostrarTodo_clicked();
}

void MainWindow::on_mostrarTodo_clicked()
{
    this->setCursor(Qt::WaitCursor);
    ui->bandejaTabla->setRowCount(0);
    m_lista.clear();
    m_lector.leer(&m_lista);

    // Se añaden los datos recuperados a la tabla
    for (size_t i = 0; i < m_lista.size(); i++)
    {
        ui->bandejaTabla->insertRow(ui->bandejaTabla->rowCount());
        int fila = ui->bandejaTabla->rowCount() - 1;
        ui->bandejaTabla->setItem(fila, COL_ID,
                                new QTableWidgetItem(m_lista[i].getIdentificador()));
        ui->bandejaTabla->setItem(fila, COL_REM,
                                new QTableWidgetItem(m_lista[i].getRem()));
        ui->bandejaTabla->setItem(fila, COL_DES,
                                new QTableWidgetItem(m_lista[i].getDestinatario()));
        ui->bandejaTabla->setItem(fila, COL_ASUNTO,
                                new QTableWidgetItem(m_lista[i].getAsunto()));
        ui->bandejaTabla->setItem(fila, COL_CC,
                                new QTableWidgetItem(m_lista[i].getCopiaCarbon()));
        ui->bandejaTabla->setItem(fila, COL_CCC,
                                new QTableWidgetItem(m_lista[i].getCopiaCarbonCiega()));
        ui->bandejaTabla->setItem(fila, COL_FECHA,
                                new QTableWidgetItem(m_lista[i].getFechaEnvio()));
        ui->bandejaTabla->setItem(fila, COL_HORA,
                                new QTableWidgetItem(m_lista[i].getHoraEnvio()));
        ui->bandejaTabla->resizeColumnToContents(fila);
    }
    this->setCursor(Qt::ArrowCursor);
}

void MainWindow::on_bandejaTabla_cellClicked(int row, int column)
{
    Q_UNUSED(column);
    m_fila = row;
}

void MainWindow::on_idBuscarPB_clicked()
{
    char idTmp[10];
    strcpy(idTmp, ui->idBuscarPB->text().toStdString().c_str());
    if (ui->buscar_barra->text().isEmpty())
        QMessageBox::warning(this, "ID vacío", "Ingrese un ID");
    else if (ui->buscar_barra->text().toULongLong() < 1 || ui->buscar_barra->text().toStdString().length() > 10
             || idTmp[0] == '0')
        QMessageBox::warning(this, "ID no válido", "El ID debe de estar en un rango de (1 - 9999999999)");
    else
    {
        Correo *correoTmp = new Correo;
        m_lista.clear();
        ui->bandejaTabla->setRowCount(0);
        correoTmp = m_lector.leer(ui->buscar_barra->text().toULong());
        if (atol(correoTmp->getIdentificador()) == ui->buscar_barra->text().toLong())
        {
            m_lista.push_back(*correoTmp);
            ui->bandejaTabla->insertRow(ui->bandejaTabla->rowCount());

            int fila = ui->bandejaTabla->rowCount() - 1;
            ui->bandejaTabla->setItem(fila, COL_ID,
                                    new QTableWidgetItem(correoTmp->getIdentificador()));
            ui->bandejaTabla->setItem(fila, COL_REM,
                                    new QTableWidgetItem(correoTmp->getRem()));
            ui->bandejaTabla->setItem(fila, COL_DES,
                                    new QTableWidgetItem(correoTmp->getDestinatario()));
            ui->bandejaTabla->setItem(fila, COL_ASUNTO,
                                    new QTableWidgetItem(correoTmp->getAsunto()));
            ui->bandejaTabla->setItem(fila, COL_CC,
                                    new QTableWidgetItem(correoTmp->getCopiaCarbon()));
            ui->bandejaTabla->setItem(fila, COL_CCC,
                                    new QTableWidgetItem(correoTmp->getCopiaCarbonCiega()));
            ui->bandejaTabla->setItem(fila, COL_FECHA,
                                    new QTableWidgetItem(correoTmp->getFechaEnvio()));
            ui->bandejaTabla->setItem(fila, COL_HORA,
                                    new QTableWidgetItem(correoTmp->getHoraEnvio()));
            ui->bandejaTabla->resizeColumnToContents(fila);
        }
    }
}

void MainWindow::on_remBuscarPB_clicked()
{
    char idTmp[10];
    strcpy(idTmp, ui->idBuscarPB->text().toStdString().c_str());
    if (ui->remLE->text().isEmpty())
        QMessageBox::warning(this, "ID vacío", "Ingrese un ID");
    else
    {
        unsigned int i;
        Correo correoTmp;
        this->setCursor(Qt::WaitCursor);
        m_lista.clear();
        ui->bandejaTabla->setRowCount(0);
        m_lector.leerRem(&m_lista, ui->remLE->text().toStdString().c_str());
        for (i = 0; i < m_lista.size(); i++)
        {
            ui->bandejaTabla->insertRow(ui->bandejaTabla->rowCount());
            int fila = ui->bandejaTabla->rowCount() - 1;
            ui->bandejaTabla->setItem(fila, COL_ID,
                                    new QTableWidgetItem(m_lista[i].getIdentificador()));
            ui->bandejaTabla->setItem(fila, COL_REM,
                                    new QTableWidgetItem(m_lista[i].getRem()));
            ui->bandejaTabla->setItem(fila, COL_DES,
                                    new QTableWidgetItem(m_lista[i].getDestinatario()));
            ui->bandejaTabla->setItem(fila, COL_ASUNTO,
                                    new QTableWidgetItem(m_lista[i].getAsunto()));
            ui->bandejaTabla->setItem(fila, COL_CC,
                                    new QTableWidgetItem(m_lista[i].getCopiaCarbon()));
            ui->bandejaTabla->setItem(fila, COL_CCC,
                                    new QTableWidgetItem(m_lista[i].getCopiaCarbonCiega()));
            ui->bandejaTabla->setItem(fila, COL_FECHA,
                                    new QTableWidgetItem(m_lista[i].getFechaEnvio()));
            ui->bandejaTabla->setItem(fila, COL_HORA,
                                    new QTableWidgetItem(m_lista[i].getHoraEnvio()));
        }
        this->setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::on_bandejaTabla_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    Q_UNUSED(row);
    Correo* tmp = m_lector.leer(ui->bandejaTabla->item(m_fila, COL_ID)->text().toULong());
    vistaPrevia p(*tmp);
    p.setModal(true);
    p.setWindowTitle("Vista previa");
    p.exec();
}

void MainWindow::on_crearCopiaPB_clicked()
{
    this->setCursor(Qt::WaitCursor);
    m_lector.crearCopiaSeguridad();
    this->setCursor(Qt::ArrowCursor);
    QMessageBox::information(this, "Copia creada", "Copia de seguridad creada exitosamente");
}
