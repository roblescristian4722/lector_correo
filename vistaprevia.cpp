#include "vistaprevia.h"
#include "ui_vistaprevia.h"

vistaPrevia::vistaPrevia(Correo correo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vistaPrevia)
{
    ui->setupUi(this);
    this->setWindowTitle("Vista Previa");
    ui->CCCLE->setText(correo.getCopiaCarbonCiega().c_str());
    ui->idLE->setText(correo.getIdentificador().c_str());
    ui->asuntoLE->setText(correo.getAsunto().c_str());
    ui->desLE->setText(correo.getDestinatario().c_str());
    ui->remLE->setText(correo.getRem().c_str());
    ui->fechaLE->setText(correo.getFechaEnvio().c_str());
    ui->horaLE->setText(correo.getHoraEnvio().c_str());
    ui->CCLE->setText(correo.getCopiaCarbon().c_str());
    ui->contenidoLE->setText(correo.getContenido().c_str());
}

vistaPrevia::~vistaPrevia()
{
    delete ui;
}
