#include "cifrar.h"
#include "ui_cifrar.h"

Cifrar::Cifrar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cifrar)
{
    ui->setupUi(this);
    this->setWindowTitle("Cifrar");
    m_personalizada = false;
}

Cifrar::~Cifrar()
{ delete ui; }

void hilo(string dest, string pass);

void Cifrar::on_contrasenaCB_stateChanged(int arg1)
{
    if (arg1)
        ui->contrasenaLE->setEnabled(true);
    else
        ui->contrasenaLE->setEnabled(false);
}

void Cifrar::activar()
{
    bool enabled = false;
    if (ui->archivoDestinoLE->text().size()){
        if (ui->contrasenaCB->isChecked()){
            if (ui->contrasenaLE->text().size())
                enabled = true;
        }
        else
            enabled = true;
    }

    if (enabled)
        ui->cifrarPB->setEnabled(true);
    else
        ui->cifrarPB->setEnabled(false);
}

void Cifrar::on_archivoDestinoLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    activar();
}

void Cifrar::on_contrasenaLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    activar();
}

void Cifrar::on_cifrarPB_clicked()
{
    string dest = ui->archivoDestinoLE->text().toStdString();
    string pass;
    fstream archivo("respaldo.csv", ios::in);
    if (!archivo.is_open())
        QMessageBox::warning(this, "Respaldo no encontrado", "No se ha encontrado un respaldo, primero intente crear uno");
    else{
        archivo.close();
        if (ui->contrasenaCB->isChecked())
            pass = ui->contrasenaLE->text().toStdString();
        else
            pass = "--auto";
        std::thread th(hilo, dest, pass);
        th.join();
        QMessageBox::information(this, "Respaldo cifrado", "Respaldo cifrado con éxito");
    }
    this->close();
}

void hilo(string dest, string pass)
{
    string tmp = "./cipher cifrar respaldo.csv ";
    tmp += dest + " " + pass;
    system("g++ cesar/main.cpp -o cipher");
    system(tmp.c_str());
}
