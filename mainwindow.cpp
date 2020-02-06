#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_tmp(nullptr)
{

    // Se inicializa la interfaz y todos sus atributos
    ui->setupUi(this);

    // Se escoge el nombre para la ventana principal
    this->setWindowTitle("Yi Mail");

    // Se coloca este mensaje para indicar que no se ha buscado ningún correo
    ui->Resultado->setText("Correo seleccionado:\n\nAún no se ha seleccionado un correo...");
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
}

void MainWindow::on_eliminar_clicked()
{
    // Aún sin implementar
}

void MainWindow::on_modificar_clicked()
{
    string id;
    if (m_tmp)
    {
        modificar m(m_tmp, &m_lector);
        m.exec();
        id = m_tmp->getIdentificador();
        std::string show = "Correo seleccionado: \n\n";
        show += "ID: " + id + "\n\n"
             +  "De: " + m_tmp->getRem() + "\n\n"
             +  "Para: " + m_tmp->getDestinatario() + "\n\n"
             +  "Asunto: " + m_tmp->getAsunto() + "\n\n"
             +  "CC: " + m_tmp->getCopiaCarbon() + "\n\n"
             +  "CCC: " + m_tmp->getCopiaCarbonCiega() + "\n\n"
             +  "Fecha de envío: " + m_tmp->getFechaEnvio() + "\n\n"
             +  "Hora de envío: " + m_tmp->getHoraEnvio() + "\n\n"
             +  "Contenido:" + "\n" + m_tmp->getContenido();
        ui->Resultado->setText(QString::fromStdString(show));
    }
    else
        QMessageBox::warning(this, "Sin correo seleccionado",
                             "No ha seleccionado ningún correo, para hacerlo busque un ID");
}

void MainWindow::on_buscar_clicked()
{
    if (ui->buscar_barra->text().isEmpty())
        QMessageBox::warning(this, "ID vacío", "Ingrese un ID");
    else if (ui->buscar_barra->text().toULongLong() < 1 || ui->buscar_barra->text().toStdString().length() > 10)
    {
        QMessageBox::warning(this, "ID no válido", "El ID debe de estar en un rango de (1 - 9999999999)");
        qDebug() << ui->buscar_barra->text().toStdString().length();
    }
    else
    {
        string id;
        Correo* tmp;
        tmp = m_lector.leer(ui->buscar_barra->text().toULongLong());
        if (atoll(tmp->getIdentificador()) != ui->buscar_barra->text().toULongLong())
            QMessageBox::warning(this, "ID no encontrado", "No se encontró el ID, primero intente agregarlo");
        else
        {
            m_tmp = tmp;
            id = m_tmp->getIdentificador();
            std::string show = "Correo seleccionado: \n\n";
            show += "ID: " + id + "\n\n"
                 +  "De: " + m_tmp->getRem() + "\n\n"
                 +  "Para: " + m_tmp->getDestinatario() + "\n\n"
                 +  "Asunto: " + m_tmp->getAsunto() + "\n\n"
                 +  "CC: " + m_tmp->getCopiaCarbon() + "\n\n"
                 +  "CCC: " + m_tmp->getCopiaCarbonCiega() + "\n\n"
                 +  "Fecha de envío: " + m_tmp->getFechaEnvio() + "\n\n"
                 +  "Hora de envío: " + m_tmp->getHoraEnvio() + "\n\n"
                 +  "Contenido:" + "\n" + m_tmp->getContenido();
            ui->Resultado->setText(QString::fromStdString(show));
        }
    }
}
