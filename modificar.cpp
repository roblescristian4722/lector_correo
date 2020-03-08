#include "modificar.h"
#include "ui_modificar.h"

modificar::modificar(LectorCorreo* lector, unsigned long index, QWidget *parent) :
    m_lector(lector),
    m_index(index),
    QDialog(parent),
    ui(new Ui::modificar)
{
    ui->setupUi(this);
    this->setWindowTitle("Modificar correo");

    m_correoTmp = m_lector->leer(index);
    ui->des_linea->setText(m_correoTmp.getDestinatario());
    ui->rem_linea->setText(m_correoTmp.getRem());
    ui->asunto_linea->setText(m_correoTmp.getAsunto());
    ui->copiaCarbon_linea->setText(m_correoTmp.getCopiaCarbon());
    ui->copiaCarbonCiega_linea->setText(m_correoTmp.getCopiaCarbonCiega());
    ui->contenido_caja->setPlainText(m_correoTmp.getContenido());
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
        m_correoTmp.setRem(rem.toStdString().c_str());
        m_correoTmp.setAsunto(asunto.toStdString().c_str());
        m_correoTmp.setContenido(cont.toStdString().c_str());
        m_correoTmp.setCopiaCarbon(cc.toStdString().c_str());
        m_correoTmp.setDestinatario(des.toStdString().c_str());
        m_correoTmp.setCopiaCarbonCiega(ccc.toStdString().c_str());

        m_lector->crear(&m_correoTmp);
        modificar::close();
    }
    else
        QMessageBox::warning(this, "Campos vacíos", "Los campos que llevan \"*\" son obligatorios");
}
