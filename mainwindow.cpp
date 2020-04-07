#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QStringList columnas;

    m_lector = new LectorCorreo(&m_indices, &m_paginados, &m_rem, &m_des);

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
    ui->opcCB->setCurrentIndex(OPC_ID);
    m_lector->guardar_indices();
    delete m_lector;
    delete ui;
}

//// MÉTODOS /////
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
        if (dato == QString(vec[size_t(m)].getRem()))
            return m;
        else if (dato < QString(vec[size_t(m)].getRem()))
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}

void MainWindow::shell_sort()
{
    size_t n = m_ids.size();
    size_t brecha = n / 2;
    size_t j;
    long tmp;
    while (brecha > 0){
        for (size_t i = brecha; i < n; ++i){
            tmp = m_ids[i];
            j = i;
            while (j >= brecha && m_ids[j - brecha] > tmp){
                m_ids[j] = m_ids[j - brecha];
                j -= brecha;
            }
            m_ids[j] = tmp;
        }
        brecha /= 2;
    }
}

void MainWindow::shell_sort(size_t n, Vector<Correo> &vec)
{
    size_t brecha = n / 2;
    size_t j;
    Correo tmp;
    while (brecha > 0){
        for (size_t i = brecha; i < n; ++i){
            tmp = vec[i];
            j = i;
            while (j >= brecha && strcmp(vec[j - brecha].getRem(), tmp.getRem()) > 0){
                vec[j] = vec[j - brecha];
                j -= brecha;
            }
            vec[j] = tmp;
        }
        brecha /= 2;
    }
}


//// SLOTS ////
/// ARCHIVO DE DATOS ///
void MainWindow::on_agregar_clicked()
{
    bool paginado = ui->opcCB->currentIndex() == OPC_IND_PAGINADOS ? true : false;
    agregar a(m_lector, paginado);
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
    else if (m_fila > ui->bandejaTabla->rowCount() || m_fila < 0)
        m_fila = 0;

    id = ui->bandejaTabla->item(m_fila, COL_ID)->text().toLong();

    // Se elimina el id de la lista de ids
    shell_sort();
    int res = busqueda_binaria(int(id));
    if (res != -1)
        m_ids.erase(size_t(res));

    // Se elimina el dato de los árboles secundarios
    aux = ui->bandejaTabla->item(m_fila, COL_REM)->text().toStdString();
    m_rem.removePrimary(aux, id);

    aux = ui->bandejaTabla->item(m_fila, COL_DES)->text().toStdString();
    m_des.removePrimary(aux, id);

    if (ui->opcCB->currentIndex() == OPC_IND_PAGINADOS)
        m_lector->eliminar(id, true);
    else
        m_lector->eliminar(id);

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
    else if (m_fila > ui->bandejaTabla->rowCount() || m_fila < 0)
        m_fila = 0;

    id = ui->bandejaTabla->item(m_fila, COL_ID)->text().toLong();

    modificar m(m_lector, id, &m_rem, &m_des);
    m.setModal(true);
    m.exec();
    on_mostrarTodo_clicked();
}

void MainWindow::on_mostrarTodo_clicked()
{
    Correo correoTmp;
    m_fila = 0;
    this->setCursor(Qt::WaitCursor);
    limpiarFilas();

    m_ids.clear();
    m_lector->leer(m_ids);

    // Se añaden los datos recuperados a la tabla
    for (size_t i = 0; i < m_ids.size(); i++){
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

/// BÚSQUEDAS ///
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
        if (ui->opcCB->currentIndex() == OPC_REM_RAM){
            int res;
            Vector<Correo> vec;

            // Se obtiene el vector
            m_lector->leerRAM(vec);

            // Se ordena
            shell_sort(vec.size(), vec);

            // Se busca el dato con búsqueda binaria
            res = busqueda_binaria(vec, ui->barraRemLE->text());

            if (res != -1)
                crearFila(vec[size_t(res)]);
        }

        /// BÚSQUEDA POR ID EN ÁRBOL BINARIO ///
        else if (ui->opcCB->currentIndex() == OPC_IND_PRIM){
            AVLTreePrimario::AVLTreeNode* nodo;
            IndicePrimario tmp;
            tmp.setLlave(ui->barraRemLE->text().toStdString().c_str());

            nodo = m_indices.findData(tmp);

            if (nodo != nullptr){
                correoTmp = m_lector->leer(nodo->dataPtr->getReferencia());
                crearFila(correoTmp);
            }
        }

        /// BÚSQUEDA POR REMITENTE/DESTINATARIO EN ÁRBOL BINARIO ///
        else if (ui->opcCB->currentIndex() == OPC_IND_SEC_REM || ui->opcCB->currentIndex() == OPC_IND_SEC_DES){
            string input = ui->barraRemLE->text().toStdString();
            LSL<IndicePrimario>* lista;
            AVLTreeSecundario::AVLTreeNode* nodo;

            if (ui->opcCB->currentIndex() == OPC_IND_SEC_REM )
                nodo = m_rem.findData(input);
            else
                nodo = m_des.findData(input);

            if (nodo != nullptr){
                lista = nodo->dataPtr->getReferencia();
                for (size_t i = 0; i < lista->size(); ++i){
                    correoTmp = m_lector->leer((*lista)[i].getReferencia());
                    crearFila(correoTmp);
                }
            }
        }
        /// BÚSQUEDA POR ÍNDICES PAGINADOS ///
        else if (ui->opcCB->currentIndex() == OPC_IND_PAGINADOS){
            IndicePrimario indiceTmp;
            indiceTmp.setLlave(ui->barraRemLE->text().toStdString().c_str());
            AVLTreePrimario::AVLTreeNode *node = m_paginados.findData(indiceTmp);
            if (node == nullptr){
                fstream archivoIndices("indices.bin", ios::in | ios::binary);
                long pos = atol(indiceTmp.getLlave().c_str()) * long(sizeof(IndicePrimario));
                indiceTmp.setLlave("");
                archivoIndices.seekg(pos);
                archivoIndices.read((char*)&indiceTmp, sizeof(IndicePrimario));
                archivoIndices.close();
                // Si el índice no se encuentra en el archivo se muestra el siguiente mensaje de error
                // y se vuelven a mostrar todos los datos
                if (ui->barraRemLE->text().toLong() != atol(indiceTmp.getLlave().c_str())){
                    QMessageBox::warning(this, "Correo no encontrado", "El correo introducido no existe");
                    on_mostrarTodo_clicked();
                    return;
                }
                // Si el índice se encontró en el archivo entonces se eliminan los índices de la lista
                // de últimos visitados
                else{
                    for (size_t i = 0; i < PAG_MAX_SIZE && i < size_t(m_paginados.getSize()); ++i)
                        cout << i + 1 << ": " << m_paginados.getLRU()[i]->getLlave() << endl;
                    m_paginados.removeLRU();
                    for (size_t i = 0; i < PAG_MAX_SIZE && i < size_t(m_paginados.getSize()); ++i)
                        cout << i + 1 << ": " << m_paginados.getLRU()[i]->getLlave() << endl;
                    AVLTreeSecundario* rem = &m_rem;
                    AVLTreeSecundario* des = &m_des;
                    m_paginados.insertData(indiceTmp, rem, des);
                    for (size_t i = 0; i < PAG_MAX_SIZE && i < size_t(m_paginados.getSize()); ++i)
                        cout << i + 1 << ": " << m_paginados.getLRU()[i]->getLlave() << endl;
                    correoTmp = m_lector->leer(indiceTmp.getReferencia());
                }
            }
            // Si el índice se encontró en el árbol entonces se actualiza al valor del nodo y se
            // reacomoda la lista
            else{
                node->time = chrono::system_clock::now().time_since_epoch().count();
                correoTmp = m_lector->leer(node->dataPtr->getReferencia());
            }
            cout << "Reacomodando nodos más visitados..." << endl;
            crearFila(correoTmp);
            cout << "<---últimos 10 elementos consulatdos:--->" << endl;
        }

        else{
            /// BÚSQUEDA POR ID EN ARCHIVO BINARIO ///
            if (ui->opcCB->currentIndex() == OPC_ID){
                correoTmp = m_lector->leer(ui->barraRemLE->text().toStdString().c_str());
                if (atol(correoTmp.getIdentificador()) == ui->barraRemLE->text().toLong())
                    m_ids.push_back(atol(correoTmp.getIdentificador()));
            }

            /// BÚSQUEDA POR REMITENTE EN ARCHIVO BINARIO ///
            else if (ui->opcCB->currentIndex() == OPC_REM)
                m_lector->leer_rem(m_ids, ui->barraRemLE->text().toStdString().c_str());

            for (i = 0; i < m_ids.size(); i++){
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

/// COPIA DE SEGURIDAD ///
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
        shell_sort();
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

        // Si el id de la copia no se encontró en la lista de
        // ids cargada en memoria
        if (res == -1){
            m_lector->crear(&correoCopia);
        }
        // En caso de que uno de los correos tenga el mismo ID que
        // uno de los almacenadosen el programa
        else{
            correoActual = m_lector->leer(to_string(m_ids[size_t(res)]).c_str());

            if (correoActual != correoCopia){
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

/// COPIA DE PROPIETARIO ///
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

void MainWindow::on_opcCB_currentIndexChanged(int index)
{
    if (index == OPC_IND_PAGINADOS){
        ui->agregar->setEnabled(false);
        ui->actionCrear_copia_de_seguridad->setEnabled(false);
        ui->actionRecuperar_copia_de_seguridad->setEnabled(false);
        ui->actionExportar_copia_de_propietario->setEnabled(false);
        if (m_indices.getSize()){
            m_rem.removeAll();
            m_des.removeAll();
            m_indices.writeFileInOrder();
            m_indices.removeAll();

            cout << "----------------------------------------------------------------"
                 << endl
                 << "Insertando índices en árbol de ind. prim. paginados..." << endl
                 << m_indices.getSize() << " " << m_paginados.getSize()      << endl;
            m_lector->cargar_archivo_indices(true);
        }
    }
    else if (index != OPC_IND_PAGINADOS){
        ui->agregar->setEnabled(true);
        ui->actionCrear_copia_de_seguridad->setEnabled(true);
        ui->actionRecuperar_copia_de_seguridad->setEnabled(true);
        ui->actionExportar_copia_de_propietario->setEnabled(true);
        if (!m_indices.getSize() && m_paginados.getSize()){
            cout << "----------------------------------------------------------------"
                 << endl
                 << "Insertando índices en árbol de ind. prim. regular..." << endl;
            m_rem.removeAll();
            m_des.removeAll();
            m_paginados.removeAll();
            m_lector->cargar_archivo_indices();
        }
    }
}
