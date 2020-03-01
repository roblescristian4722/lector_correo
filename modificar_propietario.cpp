#include "modificar_propietario.h"
#include "ui_modificar_propietario.h"

modificar_propietario::modificar_propietario(LectorCorreo* lector, QWidget *parent) :
    m_lector(lector),
    QDialog(parent),
    ui(new Ui::modificar_propietario)
{
    ui->setupUi(this);
    this->setWindowTitle("Modificar correo (copia de propietario)");
}

modificar_propietario::~modificar_propietario()
{
    delete ui;
}

void modificar_propietario::on_guardar_2_clicked()
{
    QString id, des, rem, cc, ccc, asunto, cont;
    Correo* correoTmp = new Correo;
    bool found;

    id = ui->id_linea_2->text();
    des = ui->des_linea_2->text();
    rem = ui->rem_linea_2->text();
    cc = ui->copiaCarbon_linea_2->text();
    ccc = ui->copiaCarbonCiega_linea_2->text();
    asunto = ui->asunto_linea_2->text();
    cont = ui->contenido_caja->toPlainText();

    if (id.toULongLong() < 1 || id.toULongLong() > 9999999999 || id[0] == '0')
        QMessageBox::warning(this, "ID no válido", "ID fuera del rango (1 - 9999999999)");

    else if (!id.isEmpty() && !des.isEmpty() && !rem.isEmpty())
    {
        correoTmp->setRem(rem.toStdString().c_str());
        correoTmp->setAsunto(asunto.toStdString().c_str());
        correoTmp->setContenido(cont.toStdString().c_str());
        correoTmp->setCopiaCarbon(cc.toStdString().c_str());
        correoTmp->setDestinatario(des.toStdString().c_str());
        correoTmp->setIdentificador(id.toLocal8Bit());
        correoTmp->setCopiaCarbonCiega(ccc.toStdString().c_str());

        found = m_lector->modificar_copia_propietario(correoTmp);
        if (found)
            QMessageBox::information(this, "Correo modificado", "Correo modificado con éxito");
        else
            QMessageBox::warning(this, "Correo no encontrado",
                                 "El ID solicitado no se encuentra en el archivo");
        delete correoTmp;
        correoTmp = nullptr;
        modificar_propietario::close();
    }
    else
        QMessageBox::warning(this, "Campos vacíos", "Los campos que llevan \"*\" son obligatorios");

    delete correoTmp;
    correoTmp = nullptr;
}
