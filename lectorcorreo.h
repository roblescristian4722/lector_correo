#ifndef LECTORCORREO_H
#define LECTORCORREO_H

#include <iostream>
#include "correo.h"
#include "ldl.h"
using namespace std;

class LectorCorreo
{
public:
    LectorCorreo();
    virtual ~LectorCorreo();

    const Correo& leer(size_t id);
    const Correo& leer(const char* remitente);
    void modificar(size_t id);
    void modificar(const char* remitente);
    /*void eliminar(size_t id);
    void eliminar(const char* remitente);
    void exportar(size_t id);
    void exportar(const char* remitente);
    void importar();
    void exportar();*/

    size_t getCorreos() const;
    void setCorreos(const size_t &correos);

private:
    size_t m_correosIng;

};

#endif // LECTORCORREO_H
