#include "eliminar_propietario.h"
#include "ui_eliminar_propietario.h"

eliminar_propietario::eliminar_propietario(LectorCorreo *lector, QWidget *parent) :
    m_lector(lector),
    QDialog(parent),
    ui(new Ui::eliminar_propietario)
{
    ui->setupUi(this);
}

eliminar_propietario::~eliminar_propietario()
{
    delete ui;
}

void eliminar_propietario::on_eliminarPB_clicked()
{
    bool found = false;
    QString id = ui->idLE->text();

    if (id.toULongLong() < 1 || id.toULongLong() > 9999999999 || id[0] == '0')
        QMessageBox::warning(this, "ID no válido", "ID fuera del rango (1 - 9999999999)");
    else if (!id.isEmpty())
    {
        found = m_lector->eliminar_copia_propietario(id.toLong());
        if (found)
            QMessageBox::information(this, "Correo eliminado", "Correo eliminado con éxito");
        else
            QMessageBox::information(this, "Correo no encontrado", "El ID solicitado no se encuentra en el archivo");
        this->close();
    }
    else
        QMessageBox::warning(this, "Campos vacíos", "Ingrese un ID");
}
