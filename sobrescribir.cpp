#include "sobrescribir.h"
#include "ui_sobrescribir.h"

Sobrescribir::Sobrescribir(LectorCorreo* lector, Correo* actual, Correo* copia,
                           AVLTreeSecundario* rem, AVLTreeSecundario* des, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sobrescribir)
{
    ui->setupUi(this);
    this->setWindowTitle("Correo duplicado");

    m_copia = copia;
    m_actual = actual;
    m_lector = lector;
    m_rem = rem;
    m_des = des;

    ui->idLE_copia->setText(copia->getIdentificador().c_str());
    ui->fechaLE_copia->setText(copia->getFechaEnvio().c_str());
    ui->horaLE_copia->setText(copia->getHoraEnvio().c_str());
    ui->remLE_copia->setText(copia->getRem().c_str());
    ui->desLE_copia->setText(copia->getDestinatario().c_str());
    ui->CCLE_copia->setText(copia->getCopiaCarbon().c_str());
    ui->CCCLE_copia->setText(copia->getCopiaCarbonCiega().c_str());
    ui->asuntoLE_copia->setText(copia->getAsunto().c_str());
    ui->contenidoLE_copia->setText(copia->getContenido().c_str());

    ui->idLE_actual->setText(actual->getIdentificador().c_str());
    ui->fechaLE_actual->setText(actual->getFechaEnvio().c_str());
    ui->horaLE_actual->setText(actual->getHoraEnvio().c_str());
    ui->remLE_actual->setText(actual->getRem().c_str());
    ui->desLE_actual->setText(actual->getDestinatario().c_str());
    ui->CCLE_actual->setText(actual->getCopiaCarbon().c_str());
    ui->CCCLE_actual->setText(actual->getCopiaCarbonCiega().c_str());
    ui->asuntoLE_actual->setText(actual->getAsunto().c_str());
    ui->contenidoLE_actual->setText(actual->getContenido().c_str());
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
    long id = atol(m_actual->getIdentificador().c_str());
    m_rem->removePrimary(m_actual->getRem(), id);
    m_des->removePrimary(m_actual->getDestinatario(), id);

    m_lector->crear(m_copia, true);
    this->close();
}
