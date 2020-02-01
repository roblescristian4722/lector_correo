#include "correo.h"

Correo::Correo()
{
    m_fechaEnvio[10] = {'\0'};
    m_rem[50] = {'\0'};
    m_destinatario[50] = {'\0'};
    m_copiaCarbon[100] = {'\0'};
    m_copiaCarbonCiega[100] = {'\0'};
    m_asunto[200] = {'\0'};
    m_contenido[500] = {'\0'};
}


Correo::~Correo()
{}

// Getters
size_t Correo::getIdentificador() const
{
    return m_identificador;
}

char *Correo::getAsunto() const
{
    char* tmp = new char[200];
    strcpy(tmp, m_asunto);
    return tmp;
}
char *Correo::getCopiaCarbonCiega() const
{
    char* tmp = new char[100];
    strcpy(tmp, m_copiaCarbonCiega);
    return tmp;
}
char *Correo::getCopiaCarbon() const
{
    char* tmp = new char[100];
    strcpy(tmp, m_copiaCarbon);
    return tmp;
}
char *Correo::getDestinatario() const
{
    char* tmp = new char[50];
    strcpy(tmp, m_destinatario);
    return tmp;
}
char *Correo::getRem() const
{
    char* tmp = new char[60];
    strcpy(tmp, m_rem);
    return tmp;
}
char *Correo::getFechaEnvio() const
{
    char* tmp = new char[10];
    strcpy(tmp, m_fechaEnvio);
    return tmp;
}
size_t Correo::getHoraEnvio() const
{
    return m_horaEnvio;
}

char *Correo::getContenido() const
{
    char* tmp = new char[500];
    strcpy(tmp, m_contenido);
    return tmp;
}

// Setters
void Correo::setIdentificador(const size_t &identificador)
{
    m_identificador = identificador;
}
void Correo::setContenido(const char *contenido)
{
    strcpy(m_contenido, contenido);
}
void Correo::setAsunto(const char *asunto)
{
    strcpy(m_asunto, asunto);
}
void Correo::setCopiaCarbonCiega(const char *copiaCarbonCiega)
{
    strcpy(m_copiaCarbonCiega, copiaCarbonCiega);
}
void Correo::setCopiaCarbon(const char *copiaCarbon)
{
    strcpy(m_copiaCarbon, copiaCarbon);
}
void Correo::setDestinatario(const char *destinatario)
{
    strcpy(m_destinatario, destinatario);
}
void Correo::setRem(const char *value)
{
    strcpy(m_rem, value);
}
void Correo::setFechaEnvio(const char *fechaEnvio)
{
    strcpy(m_fechaEnvio, fechaEnvio);
}
void Correo::setHoraEnvio(const size_t &horaEnvio)
{
    m_horaEnvio = horaEnvio;
}
