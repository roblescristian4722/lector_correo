#include "vistaprevia.h"
#include "ui_vistaprevia.h"

vistaPrevia::vistaPrevia(Correo correo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vistaPrevia)
{
    ui->setupUi(this);
    ui->CCCLE->setText(correo.getCopiaCarbonCiega());
    ui->idLE->setText(correo.getIdentificador());
    ui->asuntoLE->setText(correo.getAsunto());
    ui->desLE->setText(correo.getDestinatario());
    ui->remLE->setText(correo.getRem());
    ui->fechaLE->setText(correo.getFechaEnvio());
    ui->horaLE->setText(correo.getHoraEnvio());
    ui->CCLE->setText(correo.getCopiaCarbon());
    ui->contenidoLE->setText(correo.getContenido());
}

vistaPrevia::~vistaPrevia()
{
    delete ui;
}
