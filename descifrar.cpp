#include "descifrar.h"
#include "ui_descifrar.h"

Descifrar::Descifrar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Descifrar)
{
    ui->setupUi(this);
    this->setWindowTitle("Descifrar copia de seguridad");
}

Descifrar::~Descifrar()
{
    delete ui;
}

void hiloDes(string origen, string pass);

void Descifrar::on_descifrarPB_clicked()
{
    string origen = ui->nombreLE->text().toStdString();
    string pass = ui->contraseniaLE->text().toStdString();
    fstream archivo(origen, ios::in);
    fstream descifrado;
    if (!archivo.is_open())
        QMessageBox::warning(this, "Archivo cifrado no encontrado", "El archivo cifrado no existe");
    else{
        archivo.close();
        std::thread th(hiloDes, origen, pass);
        th.join();
        descifrado.open("respaldo.csv", ios::in);
        if (!descifrado.is_open())
            QMessageBox::warning(this, "Contraseña incorrecta", "La contraseña introducida es incorrecta");
        else{
            remove(origen.c_str());
            QMessageBox::information(this, "Copia de segurdad descifrada", "La copia de segurdad ha sido descifrada correctamente");
        }
    }
    this->close();
}

void Descifrar::activar()
{
    if (ui->nombreLE->text().size() && ui->contraseniaLE->text().size())
        ui->descifrarPB->setEnabled(true);
}

void Descifrar::on_nombreLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    activar();
}

void Descifrar::on_contraseniaLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    activar();
}

void hiloDes(string origen, string pass)
{
    string tmp = "./cipher descifrar ";
    tmp += origen + " respaldo.csv " + pass;
    system(tmp.c_str());
}
