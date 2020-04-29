#include "modificar.h"
#include "ui_modificar.h"

modificar::modificar(LectorCorreo* lector, long index, AVLTreeSecundario *rem,
                     AVLTreeSecundario *des, bool hash, HashMap<string, Vector<string>>* mapRem,
                     QWidget *parent) :
    m_lector(lector),
    m_rem(rem),
    m_des(des),
    m_index(index),
    m_hash(hash),
    m_mapRem(mapRem),
    QDialog(parent),
    ui(new Ui::modificar)
{
    ui->setupUi(this);
    this->setWindowTitle("Modificar correo");

    m_correoTmp = m_lector->leer(to_string(index).c_str());
    ui->des_linea->setText(m_correoTmp.getDestinatario().c_str());
    ui->rem_linea->setText(m_correoTmp.getRem().c_str());
    ui->asunto_linea->setText(m_correoTmp.getAsunto().c_str());
    ui->copiaCarbon_linea->setText(m_correoTmp.getCopiaCarbon().c_str());
    ui->copiaCarbonCiega_linea->setText(m_correoTmp.getCopiaCarbonCiega().c_str());
    ui->contenido_caja->setPlainText(m_correoTmp.getContenido().c_str());
}

modificar::~modificar()
{
    delete ui;
}

void modificar::on_guardar_clicked()
{
    QString des, rem, cc, ccc, asunto, cont;
    Vector<string> *vecStr;

    des = ui->des_linea->text();
    rem = ui->rem_linea->text();
    cc = ui->copiaCarbon_linea->text();
    ccc = ui->copiaCarbonCiega_linea->text();
    asunto = ui->asunto_linea->text();
    cont = ui->contenido_caja->toPlainText();

    if (!des.isEmpty() && !rem.isEmpty())
    {
        if (!m_hash){
            m_rem->removePrimary(m_correoTmp.getRem(), atol(m_correoTmp.getIdentificador().c_str()));
            m_des->removePrimary(m_correoTmp.getDestinatario(), atol(m_correoTmp.getIdentificador().c_str()));
        }
        else{
            vecStr = (*m_mapRem)[m_correoTmp.getRem()];
            for (size_t i = 0; i < vecStr->size(); ++i){
                if ((*vecStr)[i] == m_correoTmp.getIdentificador())
                    vecStr->erase(i);
            }
            if (!vecStr->size())
                m_mapRem->delete_value(m_correoTmp.getRem());
        }

        m_correoTmp.setRem(rem.toStdString().c_str());
        m_correoTmp.setAsunto(asunto.toStdString().c_str());
        m_correoTmp.setContenido(cont.toStdString().c_str());
        m_correoTmp.setCopiaCarbon(cc.toStdString().c_str());
        m_correoTmp.setDestinatario(des.toStdString().c_str());
        m_correoTmp.setCopiaCarbonCiega(ccc.toStdString().c_str());

        m_lector->crear(&m_correoTmp, true, m_hash);
        modificar::close();
    }
    else
        QMessageBox::warning(this, "Campos vacíos", "Los campos que llevan \"*\" son obligatorios");
}
