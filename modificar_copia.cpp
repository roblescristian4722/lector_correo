#include "modificar_copia.h"
#include "ui_modificar_copia.h"

modificar_copia::modificar_copia(LectorCorreo* lector, QWidget *parent) :
    m_lector(lector),
    QDialog(parent),
    ui(new Ui::modificar_copia)
{
    ui->setupUi(this);
    this->setWindowTitle("Modificar correo (copia de seguridad csv)");
}

modificar_copia::~modificar_copia()
{
    delete ui;
}

void modificar_copia::on_guardar_2_clicked()
{
    QString id, des, rem, cc, ccc, asunto, cont;
    Correo correoTmp;
    Parser par;
    LSL<string> data, idString;
    bool found =  false;
    unsigned int i;

    id = ui->id_linea_2->text();
    des = ui->des_linea_2->text();
    rem = ui->rem_linea_2->text();
    cc = ui->copiaCarbon_linea_2->text();
    ccc = ui->copiaCarbonCiega_linea_2->text();
    asunto = ui->asunto_linea_2->text();
    cont = ui->contenido_caja->toPlainText();

    par.getData("respaldo.csv", data);

    for (i = 0; i < data.size(); i += 9)
        idString.push_back(data[i]);

    for (i = 0; i < data.size(); i += 9)
        if (stoi(data[i]) == id.toInt())
        {
            found = true;
            break;
        }

    if (id.toULongLong() < 1 || id.toULongLong() > 9999999999 || id[0] == '0')
        QMessageBox::warning(this, "ID no válido", "ID fuera del rango (1 - 9999999999)");
    else if (!found)
    {
        QMessageBox::warning(this, "ID no encontrado",
                             "El ID no se encuentra en la copia de seguridad");
    }
    else if (!id.isEmpty() && !des.isEmpty() && !rem.isEmpty())
    {
        /*
         * Se guarda toda la información en el correo temporal
         * y luego se escribe dicho correo en el archivo binario
         * con el método "crear()" del lector
        */
        correoTmp.setRem(rem.toStdString().c_str());
        correoTmp.setAsunto(asunto.toStdString().c_str());
        correoTmp.setContenido(cont.toStdString().c_str());
        correoTmp.setCopiaCarbon(cc.toStdString().c_str());
        correoTmp.setDestinatario(des.toStdString().c_str());
        correoTmp.setIdentificador(id.toLocal8Bit());
        correoTmp.setCopiaCarbonCiega(ccc.toStdString().c_str());
        correoTmp.setFechaEnvio(data[i + 1].c_str());
        correoTmp.setHoraEnvio(data[i + 2].c_str());

        m_lector->modificar_copia(correoTmp, idString);

        QMessageBox::information(this, "Correo modificado", "Correo modificado con éxito");
        modificar_copia::close();
    }
    else
        QMessageBox::warning(this, "Campos vacíos", "Los campos que llevan \"*\" son obligatorios");
}
