#include "compresion.h"
#include "ui_compresion.h"

compresion::compresion(QString action, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::compresion)
{
    ui->setupUi(this);
    ui->tituloL->setText(action + " copia de seguridad");
    ui->accionPB->setText(action);
}

compresion::~compresion()
{
    delete ui;
}

void compresion::on_accionPB_clicked()
{
    string command;
    if (ui->accionPB->text() == "comprimir")
        command = "g++ huffman/*.cpp -o huffman.out && ./huffman.out "
                + ui->accionPB->text().toStdString() + " respaldo.csv " + ui->nombreLE->text().toStdString();
    else
        command = "g++ huffman/*.cpp -o huffman.out && ./huffman.out "
                + ui->accionPB->text().toStdString() + " " + ui->nombreLE->text().toStdString() + " respaldo.csv ";
    std::thread th(th_func, command);
    th.join();
    cout << "afasfsadf" << endl;
    if (ui->accionPB->text() == "comprimir")
        QMessageBox::information(this, "Copia de seguridad comprimida", "La copia de seguridad se ha comprimido correctamente.");
    else{
        QMessageBox::information(this, "Copia de seguridad descomprimida",
                                 "La copia de seguridad se ha descomprimido correctamente."
                                 "Se reemplazó su copia de seguridad anterior por la copia de seguridad recién descomprimida");
    }
    this->close();
}

void th_func(string command)
{
    system(command.c_str());
}
