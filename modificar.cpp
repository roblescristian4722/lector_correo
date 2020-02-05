#include "modificar.h"
#include "ui_modificar.h"

modificar::modificar(Correo* correo, LectorCorreo* lector, QWidget *parent) :
    m_correo(correo),
    m_lector(lector),
    QDialog(parent),
    ui(new Ui::modificar)
{
    ui->setupUi(this);
    this->setWindowTitle("Modificar correo");

    ui->des_linea->setText(m_correo->getDestinatario());
    ui->rem_linea->setText(m_correo->getRem());
    ui->asunto_linea->setText(m_correo->getAsunto());
    ui->contenido_caja->setPlainText(m_correo->getContenido());
    ui->copiaCarbon_linea->setText(m_correo->getCopiaCarbon());
    ui->copiaCarbonCiega_linea->setText(m_correo->getCopiaCarbonCiega());
}

modificar::~modificar()
{
    delete ui;
}

void modificar::on_guardar_clicked()
{
    QString des, rem, cc, ccc, asunto, cont;

    des = ui->des_linea->text();
    rem = ui->rem_linea->text();
    cc = ui->copiaCarbon_linea->text();
    ccc = ui->copiaCarbonCiega_linea->text();
    asunto = ui->asunto_linea->text();
    cont = ui->contenido_caja->toPlainText();

    if (!des.isEmpty() && !rem.isEmpty())
    {
        //m_correo->setIdentificador(m_id.toLoc);
        m_correo->setRem(rem.toStdString().c_str());
        m_correo->setAsunto(asunto.toStdString().c_str());
        m_correo->setContenido(cont.toStdString().c_str());
        m_correo->setCopiaCarbon(cc.toStdString().c_str());
        m_correo->setDestinatario(des.toStdString().c_str());
        m_correo->setCopiaCarbonCiega(ccc.toStdString().c_str());
        m_lector->crear(m_correo);
        modificar::close();
    }
    else
        QMessageBox::warning(this, "Campos vacíos", "Los campos que llevan \"*\" son obligatorios");
}
