#include "agregar.h"
#include "ui_agregar.h"

agregar::agregar(Correo* correo, bool* escribir, bool* pos, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::agregar),
    m_correo(correo),
    m_escribir(escribir),
    m_pos(pos)
{
    ui->setupUi(this);
}

agregar::~agregar()
{
    delete ui;
}

void agregar::on_guardar_clicked()
{
    char fechaEnvio[11];
    char horaEnvio[9];
    QString id, des, rem, cc, ccc, asunto, cont;

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

    if (id.toInt() < 1 || id.toInt() > 10)
        QMessageBox::warning(this, "ID no válido", "ID fuera del rango (1 - 10)");
    else if (!id.isEmpty() && !des.isEmpty() && !rem.isEmpty())
    {
        if (!(m_pos[id.toInt() - 1]))
        {
            m_correo->setHoraEnvio(horaEnvio);
            m_correo->setFechaEnvio(fechaEnvio);
            m_correo->setRem(rem.toStdString().c_str());
            m_correo->setAsunto(asunto.toStdString().c_str());
            m_correo->setContenido(cont.toStdString().c_str());
            m_correo->setCopiaCarbon(cc.toStdString().c_str());
            m_correo->setDestinatario(des.toStdString().c_str());
            m_correo->setIdentificador(id.toUInt());
            m_correo->setCopiaCarbonCiega(ccc.toStdString().c_str());
            *m_escribir = true;
            agregar::close();
        }
        else
        {
            QMessageBox::warning(this, "ID en uso", "El ID ingresado está en uso, seleccione otro o modifique el actual en el menú principal");
        }
    }
    else
        QMessageBox::warning(this, "Campos vacíos", "Los campos que llevan \"*\" son obligatorios");
}
