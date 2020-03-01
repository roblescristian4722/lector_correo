#include "eliminar_copia.h"
#include "ui_eliminar_copia.h"

eliminar_copia::eliminar_copia(LectorCorreo* lector, QWidget *parent) :
    m_lector(lector),
    QDialog(parent),
    ui(new Ui::eliminar_copia)
{
    ui->setupUi(this);
    this->setWindowTitle("Eliminar correo (copia de seguridad csv)");
}

eliminar_copia::~eliminar_copia()
{
    delete ui;
}

void eliminar_copia::on_eliminarPB_clicked()
{
    bool found = false;
    Parser par;
    LDL<string> data, idString;
    QString id = ui->idLE->text();

    par.getData("respaldo.csv", &data);

    for (unsigned int i = 0; i < data.size(); i += 9)
        idString.push_back(data[i]);

    for (unsigned int i = 0; i < data.size(); i += 9)
        if (stoi(data[i]) == id.toInt())
        {
            found = true;
            break;
        }

    if (id.toULongLong() < 1 || id.toULongLong() > 9999999999 || id[0] == '0')
        QMessageBox::warning(this, "ID no válido", "ID fuera del rango (1 - 9999999999)");
    else if (!found)
    {
        QMessageBox::warning(this, "ID no encontrado",
                             "El ID no se encuentra en la copia de seguridad");
    }
    else if (!id.isEmpty())
    {
        m_lector->eliminar_copia_seguridad(id.toStdString(), idString);
        QMessageBox::information(this, "Correo eliminado", "Correo eliminado con éxito");
        this->close();
    }
    else
        QMessageBox::warning(this, "Campos vacíos", "Ingrese un ID");
}
