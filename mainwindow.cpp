#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QStringList columnas;

    m_lector = new LectorCorreo(&m_indices);

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
    ui->bandejaTabla->horizontalHeader()->setVisible(true);

    on_mostrarTodo_clicked();
}

MainWindow::~MainWindow()
{
    limpiarFilas();
    m_ids.clear();
    delete m_lector;
    delete ui;
}

void MainWindow::limpiarFilas()
{
    for (int i = 0; i < ui->bandejaTabla->rowCount(); ++i)
    {
        delete ui->bandejaTabla->takeItem(i, COL_ID);
        delete ui->bandejaTabla->takeItem(i, COL_CC);
        delete ui->bandejaTabla->takeItem(i, COL_CCC);
        delete ui->bandejaTabla->takeItem(i, COL_DES);
        delete ui->bandejaTabla->takeItem(i, COL_REM);
        delete ui->bandejaTabla->takeItem(i, COL_HORA);
        delete ui->bandejaTabla->takeItem(i, COL_FECHA);
        delete ui->bandejaTabla->takeItem(i, COL_ASUNTO);
    }
    ui->bandejaTabla->setRowCount(0);
}

void MainWindow::crearFila(Correo &correo)
{
    ui->bandejaTabla->insertRow(ui->bandejaTabla->rowCount());
    int fila = ui->bandejaTabla->rowCount() - 1;

    ui->bandejaTabla->setItem(fila, COL_ID,
                            new QTableWidgetItem(correo.getIdentificador()));
    ui->bandejaTabla->setItem(fila, COL_REM,
                            new QTableWidgetItem(correo.getRem()));
    ui->bandejaTabla->setItem(fila, COL_DES,
                            new QTableWidgetItem(correo.getDestinatario()));
    ui->bandejaTabla->setItem(fila, COL_ASUNTO,
                            new QTableWidgetItem(correo.getAsunto()));
    ui->bandejaTabla->setItem(fila, COL_CC,
                            new QTableWidgetItem(correo.getCopiaCarbon()));
    ui->bandejaTabla->setItem(fila, COL_CCC,
                            new QTableWidgetItem(correo.getCopiaCarbonCiega()));
    ui->bandejaTabla->setItem(fila, COL_FECHA,
                            new QTableWidgetItem(correo.getFechaEnvio()));
    ui->bandejaTabla->setItem(fila, COL_HORA,
                            new QTableWidgetItem(correo.getHoraEnvio()));
    ui->bandejaTabla->resizeColumnToContents(fila);
}

void MainWindow::on_agregar_clicked()
{
    agregar a(m_lector, &m_indices);
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

    m_lector->eliminar(long(id), &m_indices);
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

    modificar m(m_lector, id, &m_indices);
    m.setModal(true);
    m.exec();
    on_mostrarTodo_clicked();
}

void MainWindow::on_mostrarTodo_clicked()
{
    Correo correoTmp;

    this->setCursor(Qt::WaitCursor);
    limpiarFilas();

    m_ids.clear();
    m_lector->leer(m_ids);

    // Se añaden los datos recuperados a la tabla
    for (size_t i = 0; i < m_ids.size(); i++)
    {
        correoTmp = m_lector->leer(to_string(m_ids[i]).c_str());
        crearFila(correoTmp);
    }
    this->setCursor(Qt::ArrowCursor);
}

void MainWindow::on_bandejaTabla_cellClicked(int row, int column)
{
    Q_UNUSED(column)
    m_fila = row;
}

void MainWindow::on_buscarPB_clicked()
{
    char idTmp[10];
    strcpy(idTmp, ui->buscarPB->text().toStdString().c_str());

    if (!ui->buscar_barra->text().size() && ui->opcCB->currentIndex())
        QMessageBox::warning(this, "Campo vacío", "Ingrese el ID o remitente a buscar");
    else if ((ui->buscar_barra->text().toULongLong() < 1 || ui->buscar_barra->text().toStdString().length() > 10
             || idTmp[0] == '0') && (!ui->opcCB->currentIndex() || ui->opcCB->currentIndex() == 3))
        QMessageBox::warning(this, "ID no válido", "El ID debe de estar en un rango de (1 - 9999999999)");
    else
    {
        Correo correoTmp;
        unsigned int i;

        this->setCursor(Qt::WaitCursor);
        m_ids.clear();
        ui->bandejaTabla->setRowCount(0);

        // BÚSQUEDA EN MEMORIA RAM POR REMITENTE
        if (ui->opcCB->currentIndex() == 2)
        {
            int res;
            Vector<Correo> vec;

            // Se obtiene el vector
            m_lector->leerRAM(vec);

            // Se ordena
            shell_sort(vec.size(), vec);

            // Se busca el dato con búsqueda binaria
            res = busqueda_binaria(vec, ui->buscar_barra->text());

            if (res != -1)
                crearFila(vec[res]);
        }

        // BÚSQUEDA POR ID EN ÁRBOL BINARIO
        else if (ui->opcCB->currentIndex() == 3)
        {
            AVLTree<LectorCorreo::Indice>::AVLTreeNode* nodo;
            LectorCorreo::Indice tmp;
            strcpy(tmp.llave, ui->buscar_barra->text().toStdString().c_str());

            nodo = m_indices.findData(tmp);

            if (nodo != nullptr)
            {
                correoTmp = m_lector->leer(nodo->dataPtr->referencia);
                crearFila(correoTmp);
            }
        }

        else
        {
            // BÚSQUEDA POR ID EN ARCHIVO BINARIO
            if (!ui->opcCB->currentIndex())
            {
                correoTmp = m_lector->leer(ui->buscar_barra->text().toStdString().c_str());
                if (atol(correoTmp.getIdentificador()) == ui->buscar_barra->text().toLong())
                    m_ids.push_back(atol(correoTmp.getIdentificador()));
            }

            // BÚSQUEDA POR REMITENTE EN ARCHIVO BINARIO
            else if (ui->opcCB->currentIndex() == 1)
                m_lector->leer_rem(m_ids, ui->buscar_barra->text().toStdString().c_str());

            for (i = 0; i < m_ids.size(); i++)
            {
                correoTmp = m_lector->leer(to_string(m_ids[i]).c_str());
                if (i)
                    if (m_ids[i] == m_ids[i - 1])
                        break;

                crearFila(correoTmp);
            }
        }

        this->setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::on_bandejaTabla_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column)
    Q_UNUSED(row)
    Correo tmp;
    tmp = m_lector->leer(ui->bandejaTabla->item(m_fila, COL_ID)->text().toStdString().c_str());
    vistaPrevia p(tmp);
    p.setModal(true);
    p.exec();
}

int MainWindow::busqueda_binaria(int dato)
{
    int l = 0;
        int r = int(m_ids.size() - 1);
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

int MainWindow::busqueda_binaria(Vector<Correo> &vec, QString dato)
{
    int l = 0;
        int r = int(vec.size() - 1);
        while (l <= r)
        {
            int m = (l + r) / 2;
            if (dato == QString(vec[m].getRem()))
                return m;
            else if (dato < QString(vec[m].getRem()))
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
    LDL<string> copiaDatos;
    int res;

    // Se almacenan los datos de la copia de seguridad en una lista
    // de strings cuyos valores se copiarán luego a un correo temporal
    parser.getData("respaldo.csv", copiaDatos);

    for (int i = 0; i < copiaDatos.size(); i += 9)
    {
        /* res guardará el índice de la lista que coincida con
        * el correo leído de la copia de seguridad. En caso de
        * que no se hayan encontrado coincidencias regresa un -1
        */
        res = busqueda_binaria(stoi(copiaDatos[i]));

        correoCopia.setIdentificador(copiaDatos[i].c_str());
        correoCopia.setFechaEnvio(copiaDatos[i + 1].c_str());
        correoCopia.setHoraEnvio(copiaDatos[i + 2].c_str());
        correoCopia.setRem(copiaDatos[i + 3].c_str());
        correoCopia.setDestinatario(copiaDatos[i + 4].c_str());
        correoCopia.setCopiaCarbon(copiaDatos[i + 5].c_str());
        correoCopia.setCopiaCarbonCiega(copiaDatos[i + 6].c_str());
        correoCopia.setAsunto(copiaDatos[i + 7].c_str());
        correoCopia.setContenido(copiaDatos[i + 8].c_str());

        if (res == -1)
        {
            m_ids.push_back(atol(correoCopia.getIdentificador()));
            m_lector->crear(&correoCopia, &m_indices);
        }
        // En caso de que uno de los correos tenga el mismo ID que
        // uno de los almacenadosen el programa
        else
        {
            correoActual = m_lector->leer(to_string(m_ids[res]).c_str());

            if (correoActual != correoCopia)
            {
                Sobrescribir sob(m_lector, &correoActual, &correoCopia, res, &m_indices);
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
    m_lector->crear_copia_seguridad();
    this->setCursor(Qt::ArrowCursor);
    QMessageBox::information(this, "Copia creada", "Copia de seguridad creada exitosamente");
}

void MainWindow::on_actionModificar_correo_en_copia_de_seguridad_triggered()
{
    modificar_copia mod(m_lector);
    mod.setModal(true);
    mod.exec();
}

void MainWindow::on_actionEliminar_correo_en_copia_de_seguridad_triggered()
{
    eliminar_copia elim(m_lector);
    elim.setModal(true);
    elim.exec();
}

void MainWindow::on_actionExportar_copia_de_propietario_triggered()
{
    m_lector->crear_copia_propietario();
    QMessageBox::information(this, "Copia creada", "Copia de propietario creada con éxito");
}

void MainWindow::on_actionEliminar_correo_triggered()
{
    eliminar_propietario elim(m_lector);
    elim.setModal(true);
    elim.exec();
}

void MainWindow::on_actionModificar_Correo_triggered()
{
    modificar_propietario mod(m_lector);
    mod.setModal(true);
    mod.exec();
}

void MainWindow::shell_sort(size_t n, Vector<Correo> &vec)
{
    int brecha = n / 2;
    int j;
    Correo tmp;
    while (brecha > 0)
    {
        for (int i = brecha; i < n; ++i)
        {
            tmp = vec[i];
            j = i;
            while (j >= brecha && strcmp(vec[j - brecha].getRem(), tmp.getRem()) > 0)
            {
                vec[j] = vec[j - brecha];
                j -= brecha;
            }
            vec[j] = tmp;
        }
        brecha /= 2;
    }
}
