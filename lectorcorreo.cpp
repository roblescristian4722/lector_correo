#include "lectorcorreo.h"

LectorCorreo::LectorCorreo()
{

}

LectorCorreo::~LectorCorreo()
{

}

const Correo &LectorCorreo::leer(size_t id)
{

}

const Correo &LectorCorreo::leer(const char* remitente)
{

}

void LectorCorreo::modificar(size_t id)
{

}

void LectorCorreo::modificar(const char *remitente)
{
    cout << remitente << endl;
}


// Setters y Getters
size_t LectorCorreo::getCorreos() const
{
    return m_correosIng;
}

void LectorCorreo::setCorreos(const size_t &correos)
{
    m_correosIng = correos;
}
