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

    m_ultimoLeido = 1;
    on_mostrarTodo_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_agregar_clicked()
{
    agregar a(&m_lector);
    a.setModal(true);
    a.exec();
    on_mostrarTodo_clicked();
}

void MainWindow::on_eliminar_clicked()
{
    unsigned long id;
    if (!ui->bandejaTabla->rowCount())
    {
        m_fila = 0;
        QMessageBox::warning(this, "Sin correo seleccionado",
                             "No hay correos seleccionados, intente buscar o añadir uno");
        return;
    }
    else if (m_fila >= m_ids.size() || m_fila < 0)
        m_fila = 0;

    id = ui->bandejaTabla->item(m_fila, COL_ID)->text().toULong();

    m_ids.erase(m_fila);
    m_lector.eliminar(id);
    on_mostrarTodo_clicked();
}

void MainWindow::on_modificar_clicked()
{
    unsigned long id;
    if (!ui->bandejaTabla->rowCount())
    {
        m_fila = 0;
        QMessageBox::warning(this, "Sin correo seleccionado",
                             "No hay correos seleccionados, intente buscar o añadir uno");
        return;
    }
    else if (m_fila >= m_ids.size() || m_fila < 0)
        m_fila = 0;

    id = ui->bandejaTabla->item(m_fila, COL_ID)->text().toULong();

    modificar m(&m_lector, id);
    m.setModal(true);
    m.exec();
    on_mostrarTodo_clicked();
}

void MainWindow::on_mostrarTodo_clicked()
{
    Correo correoTmp;

    this->setCursor(Qt::WaitCursor);
    ui->bandejaTabla->setRowCount(0);

    m_ids.clear();
    m_lector.leer(&m_ids);

    // Se añaden los datos recuperados a la tabla
    for (size_t i = 0; i < m_ids.size(); i++)
    {
        correoTmp = m_lector.leer(m_ids[i]);
        ui->bandejaTabla->insertRow(ui->bandejaTabla->rowCount());
        int fila = ui->bandejaTabla->rowCount() - 1;
        ui->bandejaTabla->setItem(fila, COL_ID,
                                new QTableWidgetItem(correoTmp.getIdentificador()));
        ui->bandejaTabla->setItem(fila, COL_REM,
                                new QTableWidgetItem(correoTmp.getRem()));
        ui->bandejaTabla->setItem(fila, COL_DES,
                                new QTableWidgetItem(correoTmp.getDestinatario()));
        ui->bandejaTabla->setItem(fila, COL_ASUNTO,
                                new QTableWidgetItem(correoTmp.getAsunto()));
        ui->bandejaTabla->setItem(fila, COL_CC,
                                new QTableWidgetItem(correoTmp.getCopiaCarbon()));
        ui->bandejaTabla->setItem(fila, COL_CCC,
                                new QTableWidgetItem(correoTmp.getCopiaCarbonCiega()));
        ui->bandejaTabla->setItem(fila, COL_FECHA,
                                new QTableWidgetItem(correoTmp.getFechaEnvio()));
        ui->bandejaTabla->setItem(fila, COL_HORA,
                                new QTableWidgetItem(correoTmp.getHoraEnvio()));
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
        Correo correoTmp;
        m_ids.clear();
        ui->bandejaTabla->setRowCount(0);
        correoTmp = m_lector.leer(ui->buscar_barra->text().toULong());
        if (atol(correoTmp.getIdentificador()) == ui->buscar_barra->text().toLong())
        {
            m_ids.push_back(atol(correoTmp.getIdentificador()));
            ui->bandejaTabla->insertRow(ui->bandejaTabla->rowCount());

            int fila = ui->bandejaTabla->rowCount() - 1;
            ui->bandejaTabla->setItem(fila, COL_ID,
                                    new QTableWidgetItem(correoTmp.getIdentificador()));
            ui->bandejaTabla->setItem(fila, COL_REM,
                                    new QTableWidgetItem(correoTmp.getRem()));
            ui->bandejaTabla->setItem(fila, COL_DES,
                                    new QTableWidgetItem(correoTmp.getDestinatario()));
            ui->bandejaTabla->setItem(fila, COL_ASUNTO,
                                    new QTableWidgetItem(correoTmp.getAsunto()));
            ui->bandejaTabla->setItem(fila, COL_CC,
                                    new QTableWidgetItem(correoTmp.getCopiaCarbon()));
            ui->bandejaTabla->setItem(fila, COL_CCC,
                                    new QTableWidgetItem(correoTmp.getCopiaCarbonCiega()));
            ui->bandejaTabla->setItem(fila, COL_FECHA,
                                    new QTableWidgetItem(correoTmp.getFechaEnvio()));
            ui->bandejaTabla->setItem(fila, COL_HORA,
                                    new QTableWidgetItem(correoTmp.getHoraEnvio()));
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
        m_ids.clear();
        ui->bandejaTabla->setRowCount(0);
        m_lector.leer_rem(&m_ids, ui->remLE->text().toStdString().c_str());

        for (i = 0; i < m_ids.size(); i++)
        {
            correoTmp = m_lector.leer(m_ids[i]);

            ui->bandejaTabla->insertRow(ui->bandejaTabla->rowCount());
            int fila = ui->bandejaTabla->rowCount() - 1;
            ui->bandejaTabla->setItem(fila, COL_ID,
                                    new QTableWidgetItem(correoTmp.getIdentificador()));
            ui->bandejaTabla->setItem(fila, COL_REM,
                                    new QTableWidgetItem(correoTmp.getRem()));
            ui->bandejaTabla->setItem(fila, COL_DES,
                                    new QTableWidgetItem(correoTmp.getDestinatario()));
            ui->bandejaTabla->setItem(fila, COL_ASUNTO,
                                    new QTableWidgetItem(correoTmp.getAsunto()));
            ui->bandejaTabla->setItem(fila, COL_CC,
                                    new QTableWidgetItem(correoTmp.getCopiaCarbon()));
            ui->bandejaTabla->setItem(fila, COL_CCC,
                                    new QTableWidgetItem(correoTmp.getCopiaCarbonCiega()));
            ui->bandejaTabla->setItem(fila, COL_FECHA,
                                    new QTableWidgetItem(correoTmp.getFechaEnvio()));
            ui->bandejaTabla->setItem(fila, COL_HORA,
                                    new QTableWidgetItem(correoTmp.getHoraEnvio()));
        }
        this->setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::on_bandejaTabla_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    Q_UNUSED(row);
    Correo tmp = m_lector.leer(ui->bandejaTabla->item(m_fila, COL_ID)->text().toULong());
    vistaPrevia p(tmp);
    p.setModal(true);
    p.exec();
}

int MainWindow::busqueda_binaria(int dato)
{
    int l = 0;
        int r = m_ids.size() - 1;
        while (l <= r)
        {
            int m = (l + r) / 2;
            if (dato == m_ids[m])
                return m;
            else if (dato < m_ids[m])
                r = m - 1;
            else
                l = m + 1;
        }
        return -1;
}

int MainWindow::busqueda_binaria(Vector<Correo>* vec, QString dato)
{
    int l = 0;
        int r = vec->size() - 1;
        while (l <= r)
        {
            int m = (l + r) / 2;
            if (dato == QString((*vec)[m].getRem()))
                return m;
            else if (dato < QString((*vec)[m].getRem()))
                r = m - 1;
            else
                l = m + 1;
        }
        return -1;
}

void MainWindow::on_actionRecuperar_copia_de_seguridad_triggered()
{
    Parser parser;
    Correo correoActual;
    Correo correoCopia;
    LDL<string> *copiaDatos = new LDL<string>;
    int res;

    // Se almacenan los datos de la copia de seguridad en una lista
    // de strings cuyos valores se copiarán luego a un correo temporal
    parser.getData("respaldo.csv", copiaDatos);

    for (int i = 0; i < copiaDatos->size(); i += 9)
    {
        /* res guardará el índice de la lista que coincida con
        * el correo leído de la copia de seguridad. En caso de
        * que no se hayan encontrado coincidencias regresa un -1
        */
        res = busqueda_binaria(stoi((*copiaDatos)[i]));

        correoCopia.setIdentificador((*copiaDatos)[i].c_str());
        correoCopia.setFechaEnvio((*copiaDatos)[i + 1].c_str());
        correoCopia.setHoraEnvio((*copiaDatos)[i + 2].c_str());
        correoCopia.setRem((*copiaDatos)[i + 3].c_str());
        correoCopia.setDestinatario((*copiaDatos)[i + 4].c_str());
        correoCopia.setCopiaCarbon((*copiaDatos)[i + 5].c_str());
        correoCopia.setCopiaCarbonCiega((*copiaDatos)[i + 6].c_str());
        correoCopia.setAsunto((*copiaDatos)[i + 7].c_str());
        correoCopia.setContenido((*copiaDatos)[i + 8].c_str());

        if (res == -1)
        {
            m_ids.push_back(atol(correoCopia.getIdentificador()));
            m_lector.crear(&correoCopia);
        }
        // En caso de que uno de los correos tenga el mismo ID que
        // uno de los almacenadosen el programa
        else
        {
            correoActual = m_lector.leer(m_ids[res]);

            if (correoActual != correoCopia)
            {
                Sobrescribir sob(&m_lector, &correoActual, &correoCopia, res);
                sob.setModal(true);
                sob.exec();
            }
        }
    }
    on_mostrarTodo_clicked();
    QMessageBox::information(this, "Copia de seguridad restaurada", "Copia de seguridad restaurada con éxito");
}

void MainWindow::on_actionCrear_copia_de_seguridad_triggered()
{
    this->setCursor(Qt::WaitCursor);
    m_lector.crear_copia_seguridad();
    this->setCursor(Qt::ArrowCursor);
    QMessageBox::information(this, "Copia creada", "Copia de seguridad creada exitosamente");
}

void MainWindow::on_actionModificar_correo_en_copia_de_seguridad_triggered()
{
    modificar_copia mod(&m_lector);
    mod.setModal(true);
    mod.exec();
}

void MainWindow::on_actionEliminar_correo_en_copia_de_seguridad_triggered()
{
    eliminar_copia elim(&m_lector);
    elim.setModal(true);
    elim.exec();
}

void MainWindow::on_actionExportar_copia_de_propietario_triggered()
{
    m_lector.crear_copia_propietario();
    QMessageBox::information(this, "Copia creada", "Copia de propietario creada con éxito");
}

void MainWindow::on_actionEliminar_correo_triggered()
{
    eliminar_propietario elim(&m_lector);
    elim.setModal(true);
    elim.exec();
}

void MainWindow::on_actionModificar_Correo_triggered()
{
    modificar_propietario mod(&m_lector);
    mod.setModal(true);
    mod.exec();
}

void MainWindow::on_remRAMPB_clicked()
{
    int res;
    if (ui->remRAMLE->text().isEmpty())
        QMessageBox::warning(this, "Remitente vacío", "Ingrese un remitente");
    else
    {
        Vector<Correo> *vec = new Vector<Correo>;
        // Se obtiene el vector
        m_lector.leerRAM(vec);
        // Se ordena
        shell_sort(vec->size(), vec);
        // Se busca el dato con búsqueda binaria
        res = busqueda_binaria(vec, ui->remRAMLE->text());

        if (res == -1)
            QMessageBox::warning(this, "Remitente no encontrado",
                                 "No se ha encontrado el remitente proporcionado");
        else
        {
            ui->bandejaTabla->setRowCount(0);

            ui->bandejaTabla->insertRow(ui->bandejaTabla->rowCount());
            int fila = ui->bandejaTabla->rowCount() - 1;
            ui->bandejaTabla->setItem(fila, COL_ID,
                                    new QTableWidgetItem((*vec)[res].getIdentificador()));
            ui->bandejaTabla->setItem(fila, COL_REM,
                                    new QTableWidgetItem((*vec)[res].getRem()));
            ui->bandejaTabla->setItem(fila, COL_DES,
                                    new QTableWidgetItem((*vec)[res].getDestinatario()));
            ui->bandejaTabla->setItem(fila, COL_ASUNTO,
                                    new QTableWidgetItem((*vec)[res].getAsunto()));
            ui->bandejaTabla->setItem(fila, COL_CC,
                                    new QTableWidgetItem((*vec)[res].getCopiaCarbon()));
            ui->bandejaTabla->setItem(fila, COL_CCC,
                                    new QTableWidgetItem((*vec)[res].getCopiaCarbonCiega()));
            ui->bandejaTabla->setItem(fila, COL_FECHA,
                                    new QTableWidgetItem((*vec)[res].getFechaEnvio()));
            ui->bandejaTabla->setItem(fila, COL_HORA,
                                    new QTableWidgetItem((*vec)[res].getHoraEnvio()));
        }
        delete vec;
    }
}

void MainWindow::shell_sort(size_t n, Vector<Correo>* vec)
{
    char tmp[50];
    int brecha = n / 2;
    int j;
    while (brecha > 0)
    {
        for (int i = brecha; i < n; ++i)
        {
            strcpy(tmp, (*vec)[i].getRem());
            j = i;
            while (j >= brecha && strcmp((*vec)[j - brecha].getRem(), tmp) > 0)
            {
                (*vec)[j].setRem((*vec)[j - brecha].getRem());
                j -= brecha;
            }
            (*vec)[j].setRem(tmp);
        }
        brecha /= 2;
    }
}
