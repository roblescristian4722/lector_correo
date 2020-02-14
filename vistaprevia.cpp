#include "vistaprevia.h"
#include "ui_vistaprevia.h"

vistaPrevia::vistaPrevia(Correo correo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vistaPrevia)
{
    char contenidoTmp[500];
    strcpy(contenidoTmp, correo.getContenido());
    for(int i = 0; i < 500; i++)
        if (contenidoTmp[i] == '|' && contenidoTmp[i + 1] == '~'
            && contenidoTmp[i + 2] == '|')
        {
            contenidoTmp[i] = '\0';
            break;
        }

    ui->setupUi(this);
    ui->CCCLE->setText(correo.getCopiaCarbonCiega());
    ui->idLE->setText(correo.getIdentificador());
    ui->asuntoLE->setText(correo.getAsunto());
    ui->desLE->setText(correo.getDestinatario());
    ui->remLE->setText(correo.getRem());
    ui->fechaLE->setText(correo.getFechaEnvio());
    ui->horaLE->setText(correo.getHoraEnvio());
    ui->CCLE->setText(correo.getCopiaCarbon());
    ui->contenidoLE->setText(contenidoTmp);
}

vistaPrevia::~vistaPrevia()
{
    delete ui;
}
