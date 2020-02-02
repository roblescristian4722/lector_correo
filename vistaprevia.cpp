#include "vistaprevia.h"
#include "ui_vistaprevia.h"

vistaprevia::vistaprevia(Correo* correo, QWidget *parent) :
    m_correo(correo),
    QDialog(parent),
    ui(new Ui::vistaprevia)
{
    ui->setupUi(this);
    this->setWindowTitle("Vista Previa");

    ui->cc_res->setText(m_correo->getCopiaCarbon());
    ui->id_res->setText(QString::number(m_correo->getIdentificador()));
    ui->ccc_res->setText(m_correo->getCopiaCarbonCiega());
    ui->des_res->setText(m_correo->getDestinatario());
    ui->rem_res->setText(m_correo->getRem());
    ui->asunto_res->setText(m_correo->getAsunto());
    ui->fechaEnvio_res->setText(m_correo->getFechaEnvio());
    ui->horaEnvio_res->setText(m_correo->getHoraEnvio());
    ui->contenido_res->setText(m_correo->getContenido());
}

vistaprevia::~vistaprevia()
{
    delete ui;
}
