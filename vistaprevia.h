#ifndef VISTAPREVIA_H
#define VISTAPREVIA_H

#include <QDialog>
#include "correo.h"

namespace Ui {
class vistaPrevia;
}

class vistaPrevia : public QDialog
{
    Q_OBJECT

public:
    explicit vistaPrevia(Correo correo, QWidget *parent = nullptr);
    ~vistaPrevia();

private:
    Ui::vistaPrevia *ui;
};

#endif // VISTAPREVIA_H
