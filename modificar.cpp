#include "modificar.h"
#include "ui_modificar.h"

modificar::modificar(LDL<Correo>* lista, LectorCorreo* lector, unsigned long index, QWidget *parent) :
    m_lista(lista),
    m_lector(lector),
    m_index(index),
    QDialog(parent),
    ui(new Ui::modificar)
{
    ui->setupUi(this);
    this->setWindowTitle("Modificar correo");

    ui->des_linea->setText((*m_lista)[index].getDestinatario());
    ui->rem_linea->setText((*m_lista)[index].getRem());
    ui->asunto_linea->setText((*m_lista)[index].getAsunto());
    ui->contenido_caja->setPlainText((*m_lista)[index].getContenido());
    ui->copiaCarbon_linea->setText((*m_lista)[index].getCopiaCarbon());
    ui->copiaCarbonCiega_linea->setText((*m_lista)[index].getCopiaCarbonCiega());
}

modificar::~modificar()
{
    delete ui;
}

void modificar::on_guardar_clicked()
{
    QString des, rem, cc, ccc, asunto, cont;
    Correo tmp = (*m_lista)[m_index];

    des = ui->des_linea->text();
    rem = ui->rem_linea->text();
    cc = ui->copiaCarbon_linea->text();
    ccc = ui->copiaCarbonCiega_linea->text();
    asunto = ui->asunto_linea->text();
    cont = ui->contenido_caja->toPlainText();

    if (!des.isEmpty() && !rem.isEmpty())
    {
        tmp.setRem(rem.toStdString().c_str());
        tmp.setAsunto(asunto.toStdString().c_str());
        tmp.setContenido(cont.toStdString().c_str());
        tmp.setCopiaCarbon(cc.toStdString().c_str());
        tmp.setDestinatario(des.toStdString().c_str());
        tmp.setCopiaCarbonCiega(ccc.toStdString().c_str());
        (*m_lista).erase(m_index);
        (*m_lista).insert(tmp, m_index);
        m_lector->crear(&tmp);
        modificar::close();
    }
    else
        QMessageBox::warning(this, "Campos vacíos", "Los campos que llevan \"*\" son obligatorios");
}
