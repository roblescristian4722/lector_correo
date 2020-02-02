#ifndef VISTAPREVIA_H
#define VISTAPREVIA_H

#include <QDialog>
#include "correo.h"

namespace Ui {
class vistaprevia;
}

class vistaprevia : public QDialog
{
    Q_OBJECT

public:
    explicit vistaprevia(Correo* correo, QWidget *parent = nullptr);
    ~vistaprevia();

private:
    Ui::vistaprevia *ui;

    Correo* m_correo;
};

#endif // VISTAPREVIA_H
