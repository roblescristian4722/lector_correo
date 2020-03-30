#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QStringList columnas;

    m_lector = new LectorCorreo(&m_indices, &m_rem, &m_des);

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

    // Se recuperan los datos del archivo binario en la
    // lista doblemente ligada que forma parte de la clase
    ui->bandejaTabla->horizontalHeader()->setVisible(true);

    m_rem.parseInOrder();
    m_des.parseInOrder();
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
    while (ui->bandejaTabla->rowCount())
        ui->bandejaTabla->removeRow(0);
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
    m_rem.parseInOrder();
    m_des.parseInOrder();
    on_mostrarTodo_clicked();
}

void MainWindow::on_eliminar_clicked()
{
    long id;
    string aux;
    if (!ui->bandejaTabla->rowCount())
    {
        m_fila = 0;
        QMessageBox::warning(this, "Sin correo seleccionado",
                             "No hay correos seleccionados, intente buscar o añadir uno");
        return;
    }

    id = ui->bandejaTabla->item(m_fila, COL_ID)->text().toLong();

    aux = ui->bandejaTabla->item(m_fila, COL_REM)->text().toStdString();
    m_rem.removePrimary(aux, id);

    aux = ui->bandejaTabla->item(m_fila, COL_DES)->text().toStdString();
    m_des.removePrimary(aux, id);

    m_lector->eliminar(id, &m_indices);

    m_rem.parseInOrder();
    m_des.parseInOrder();
    on_mostrarTodo_clicked();
}

void MainWindow::on_modificar_clicked()
{
    long id;
    if (!ui->bandejaTabla->rowCount())
    {
        m_fila = 0;
        QMessageBox::warning(this, "Sin correo seleccionado",
                             "No hay correos seleccionados, intente buscar o añadir uno");
        return;
    }

    id = ui->bandejaTabla->item(m_fila, COL_ID)->text().toLong();

    modificar m(m_lector, id, &m_indices, &m_rem, &m_des);
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
    cout << "row: " << row << endl;
}

void MainWindow::on_buscarPB_clicked()
{
    char idTmp[10];
    strcpy(idTmp, ui->buscarPB->text().toStdString().c_str());

    if (!ui->barraRemLE->text().size() && ui->opcCB->currentIndex())
        QMessageBox::warning(this, "Campo vacío", "Ingrese el ID o remitente a buscar");
    else if ((ui->barraRemLE->text().toULongLong() < 1 || ui->barraRemLE->text().toStdString().length() > 10
             || idTmp[0] == '0') && (!ui->opcCB->currentIndex() || ui->opcCB->currentIndex() == 3))
        QMessageBox::warning(this, "ID no válido", "El ID debe de estar en un rango de (1 - 9999999999)");
    else
    {
        Correo correoTmp;
        unsigned int i;

        this->setCursor(Qt::WaitCursor);
        m_ids.clear();
        limpiarFilas();

        /// BÚSQUEDA EN MEMORIA RAM POR REMITENTE ///
        if (ui->opcCB->currentIndex() == OPC_REM_RAM)
        {
            int res;
            Vector<Correo> vec;

            // Se obtiene el vector
            m_lector->leerRAM(vec);

            // Se ordena
            shell_sort(vec.size(), vec);

            // Se busca el dato con búsqueda binaria
            res = busqueda_binaria(vec, ui->barraRemLE->text());

            if (res != -1)
                crearFila(vec[res]);
        }

        /// BÚSQUEDA POR ID EN ÁRBOL BINARIO ///
        else if (ui->opcCB->currentIndex() == OPC_IND_PRIM)
        {
            AVLTreePrimario::AVLTreeNode* nodo;
            IndicePrimario tmp;
            tmp.setLlave(ui->barraRemLE->text().toStdString().c_str());

            nodo = m_indices.findData(tmp);

            if (nodo != nullptr)
            {
                correoTmp = m_lector->leer(nodo->dataPtr->getReferencia());
                crearFila(correoTmp);
            }
        }

        /// BÚSQUEDA POR REMITENTE/DESTINATARIO EN ÁRBOL BINARIO ///
        else if (ui->opcCB->currentIndex() == OPC_IND_SEC_REM || ui->opcCB->currentIndex() == OPC_IND_SEC_DES)
        {
            string input = ui->barraRemLE->text().toStdString();
            LSL<IndicePrimario>* lista;
            AVLTreeSecundario::AVLTreeNode* nodo;

            if (ui->opcCB->currentIndex() == OPC_IND_SEC_REM )
                nodo = m_rem.findData(input);
            else
                nodo = m_des.findData(input);

            if (nodo != nullptr)
            {
                lista = nodo->dataPtr->getReferencia();
                for (size_t i = 0; i < lista->size(); ++i)
                {
                    correoTmp = m_lector->leer((*lista)[i].getReferencia());
                    crearFila(correoTmp);
                }
            }
        }

        else
        {
            /// BÚSQUEDA POR ID EN ARCHIVO BINARIO ///
            if (ui->opcCB->currentIndex() == OPC_ID)
            {
                correoTmp = m_lector->leer(ui->barraRemLE->text().toStdString().c_str());
                if (atol(correoTmp.getIdentificador()) == ui->barraRemLE->text().toLong())
                    m_ids.push_back(atol(correoTmp.getIdentificador()));
            }

            /// BÚSQUEDA POR REMITENTE EN ARCHIVO BINARIO ///
            else if (ui->opcCB->currentIndex() == OPC_REM)
                m_lector->leer_rem(m_ids, ui->barraRemLE->text().toStdString().c_str());

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
    LSL<string> copiaDatos;
    int res;

    // Se almacenan los datos de la copia de seguridad en una lista
    // de strings cuyos valores se copiarán luego a un correo temporal
    parser.getData("respaldo.csv", copiaDatos);

    for (size_t i = 0; i < copiaDatos.size(); i += 9)
    {
        // res guardará el índice de la lista que coincida con
        // el correo leído de la copia de seguridad. En caso de
        // que no se hayan encontrado coincidencias regresa un -1
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
            correoActual = m_lector->leer(to_string(m_ids[size_t(res)]).c_str());

            if (correoActual != correoCopia)
            {
                Sobrescribir sob(m_lector, &correoActual, &correoCopia, &m_rem, &m_des);
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
    size_t brecha = n / 2;
    size_t j;
    Correo tmp;
    while (brecha > 0)
    {
        for (size_t i = brecha; i < n; ++i)
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

void MainWindow::on_opcCB_currentIndexChanged(int index)
{}
