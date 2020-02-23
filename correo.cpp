#include "correo.h"

Correo::Correo()
{
}

Correo::~Correo()
{}

// Getters
char* Correo::getIdentificador() const
{
    char* tmp = new char[11];
    strcpy(tmp, m_identificador);
    return tmp;
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
char *Correo::getHoraEnvio() const
{
    char* tmp = new char[6];
    strcpy(tmp, m_horaEnvio);
    return tmp;
}

char *Correo::getContenido() const
{
    char* tmp = new char[500];
    strcpy(tmp, m_contenido);
    return tmp;
}

// Setters
void Correo::setIdentificador(const char* identificador)
{
    strcpy(m_identificador, identificador);
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

bool Correo::operator ==(Correo &correo2)
{
    if (!strcmp(this->getIdentificador(), correo2.getIdentificador()))
        if (!strcmp(this->getFechaEnvio(), correo2.getFechaEnvio()))
            if(!strcmp(this->getHoraEnvio(), correo2.getHoraEnvio()))
                if(!strcmp(this->getRem(), correo2.getRem()))
                    if(!strcmp(this->getDestinatario(), correo2.getDestinatario()))
                        if (!strcmp(this->getCopiaCarbon(), correo2.getCopiaCarbon()))
                            if (!strcmp(this->getCopiaCarbonCiega(), correo2.getCopiaCarbonCiega()))
                                if (!strcmp(this->getAsunto(), correo2.getAsunto()))
                                    if (!strcmp(this->getContenido(), correo2.getContenido()))
                                        return true;
    return false;
}

bool Correo::operator !=(Correo &correo2)
{
    if (strcmp(this->getFechaEnvio(), correo2.getFechaEnvio()))
        return true;
    if(strcmp(this->getHoraEnvio(), correo2.getHoraEnvio()))
        return true;
    if(strcmp(this->getRem(), correo2.getRem()))
        return true;
    if(strcmp(this->getDestinatario(), correo2.getDestinatario()))
        return true;
    if (strcmp(this->getCopiaCarbon(), correo2.getCopiaCarbon()))
        return true;
    if (strcmp(this->getCopiaCarbonCiega(), correo2.getCopiaCarbonCiega()))
        return true;
    if (strcmp(this->getAsunto(), correo2.getAsunto()))
        return true;
    if (strcmp(this->getContenido(), correo2.getContenido()))
        return true;
    return false;
}
void Correo::setHoraEnvio(const char *horaEnvio)
{
    strcpy(m_horaEnvio, horaEnvio);
}
