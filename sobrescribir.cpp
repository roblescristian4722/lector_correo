#include "sobrescribir.h"
#include "ui_sobrescribir.h"

Sobrescribir::Sobrescribir(LectorCorreo* lector, LDL<Correo>* actual, Correo* copia, int index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sobrescribir)
{
    ui->setupUi(this);
    this->setWindowTitle("Correo duplicado");

    m_actual = actual;
    m_index = index;
    m_copia = copia;

    ui->idLE_copia->setText(copia->getIdentificador());
    ui->fechaLE_copia->setText(copia->getFechaEnvio());
    ui->horaLE_copia->setText(copia->getHoraEnvio());
    ui->remLE_copia->setText(copia->getRem());
    ui->desLE_copia->setText(copia->getDestinatario());
    ui->CCLE_copia->setText(copia->getCopiaCarbon());
    ui->CCCLE_copia->setText(copia->getCopiaCarbonCiega());
    ui->asuntoLE_copia->setText(copia->getAsunto());
    ui->contenidoLE_copia->setText(copia->getContenido());

    ui->idLE_actual->setText((*actual)[index].getIdentificador());
    ui->fechaLE_actual->setText((*actual)[index].getFechaEnvio());
    ui->horaLE_actual->setText((*actual)[index].getHoraEnvio());
    ui->remLE_actual->setText((*actual)[index].getRem());
    ui->desLE_actual->setText((*actual)[index].getDestinatario());
    ui->CCLE_actual->setText((*actual)[index].getCopiaCarbon());
    ui->CCCLE_actual->setText((*actual)[index].getCopiaCarbonCiega());
    ui->asuntoLE_actual->setText((*actual)[index].getAsunto());
    ui->contenidoLE_actual->setText((*actual)[index].getContenido());
}

Sobrescribir::~Sobrescribir()
{
    delete ui;
}

void Sobrescribir::on_actualPB_clicked()
{
    this->close();
}

void Sobrescribir::on_copiaPB_clicked()
{
    m_actual->erase(m_index);
    m_actual->insert(*m_copia, m_index);
    m_lector->crear(m_copia);
    this->close();
}
