#include "agregar.h"
#include "ui_agregar.h"

agregar::agregar(LectorCorreo* lector, AVLTree<LectorCorreo::Indice>* indices, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::agregar),
    m_lector(lector),
    m_indices(indices)
{
    ui->setupUi(this);
    this->setWindowTitle("Agregar correo");
}

agregar::~agregar()
{
    delete ui;
}

void agregar::on_guardar_clicked()
{
    char fechaEnvio[11];
    char horaEnvio[9];
    char idVer[10];
    QString id, des, rem, cc, ccc, asunto, cont;
    Correo correo;
    Correo tmp;

    // Se obtiene la fecha del sistema
    time_t now = time(0);
    tm * time = localtime(&now);
    snprintf(fechaEnvio, sizeof(fechaEnvio), "%s/%s/%s", to_string(time->tm_mday).c_str(),
            to_string(time->tm_mon + 1).c_str(), to_string(time->tm_year + 1900).c_str());
    snprintf(horaEnvio, sizeof(horaEnvio), "%d:%d:%d", time->tm_hour, time->tm_min, time->tm_sec);

    id = ui->id_linea->text();
    des = ui->des_linea->text();
    rem = ui->rem_linea->text();
    cc = ui->copiaCarbon_linea->text();
    ccc = ui->copiaCarbonCiega_linea->text();
    asunto = ui->asunto_linea->text();
    cont = ui->contenido_caja->toPlainText();

    tmp = m_lector->leer(id.toStdString().c_str());

    if (id.toULongLong() < 1 || id.toULongLong() > 9999999999 || id[0] == '0')
        QMessageBox::warning(this, "ID no válido", "ID fuera del rango (1 - 9999999999)");
    else if (atoll(tmp.getIdentificador()) == id.toLongLong())
        QMessageBox::warning(this, "ID en uso",
                             "El ID está en uso, utilice uno nuevo o modifique el ya existente");
    else if (!id.isEmpty() && !des.isEmpty() && !rem.isEmpty())
    {
        /*
         * Se guarda toda la información en el correo temporal
         * y luego se escribe dicho correo en el archivo binario
         * con el método "crear()" del lector
        */
        correo.setHoraEnvio(horaEnvio);
        correo.setFechaEnvio(fechaEnvio);
        correo.setRem(rem.toStdString().c_str());
        correo.setAsunto(asunto.toStdString().c_str());
        correo.setContenido(cont.toStdString().c_str());
        correo.setCopiaCarbon(cc.toStdString().c_str());
        correo.setDestinatario(des.toStdString().c_str());
        correo.setIdentificador(id.toLocal8Bit());
        correo.setCopiaCarbonCiega(ccc.toStdString().c_str());

        m_lector->crear(&correo, m_indices);
        agregar::close();
    }
    else
        QMessageBox::warning(this, "Campos vacíos", "Los campos que llevan \"*\" son obligatorios");
}
