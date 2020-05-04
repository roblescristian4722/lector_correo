#include "correo.h"

Correo::Correo(){}

Correo::~Correo(){}

// Getters
string Correo::getIdentificador() const
{ return m_identificador; }

string Correo::getAsunto() const
{ return m_asunto; }

string Correo::getCopiaCarbonCiega() const
{ return m_copiaCarbonCiega; }

string Correo::getCopiaCarbon() const
{ return m_copiaCarbon; }

string Correo::getDestinatario() const
{ return m_destinatario; }

string Correo::getRem() const
{ return m_rem; }

string Correo::getFechaEnvio() const
{ return m_fechaEnvio; }

string Correo::getHoraEnvio() const
{ return m_horaEnvio; }

string Correo::getContenido() const
{ return m_contenido; }

// Setters
void Correo::setIdentificador(const char* identificador)
{ strcpy(m_identificador, identificador); }

void Correo::setContenido(const char* contenido)
{ strcpy(m_contenido, contenido); }

void Correo::setAsunto(const char* asunto)
{ strcpy(m_asunto, asunto); }

void Correo::setCopiaCarbonCiega(const char* copiaCarbonCiega)
{ strcpy(m_copiaCarbonCiega, copiaCarbonCiega); }

void Correo::setCopiaCarbon(const char* copiaCarbon)
{ strcpy(m_copiaCarbon, copiaCarbon); }

void Correo::setDestinatario(const char* destinatario)
{ strcpy(m_destinatario, destinatario); }

void Correo::setRem(const char* value)
{ strcpy(m_rem, value); }

void Correo::setFechaEnvio(const char* fechaEnvio)
{ strcpy(m_fechaEnvio, fechaEnvio); }

void Correo::setHoraEnvio(const char* horaEnvio)
{ strcpy(m_horaEnvio, horaEnvio); }

bool Correo::operator ==(Correo &correo2)
{
    if (this->getIdentificador() == correo2.getIdentificador())
        if (this->getFechaEnvio() == correo2.getFechaEnvio())
            if(this->getHoraEnvio() == correo2.getHoraEnvio())
                if(this->getRem() == correo2.getRem())
                    if(this->getDestinatario() == correo2.getDestinatario())
                        if (this->getCopiaCarbon() == correo2.getCopiaCarbon())
                            if (this->getCopiaCarbonCiega() == correo2.getCopiaCarbonCiega())
                                if (this->getAsunto() == correo2.getAsunto())
                                    if (this->getContenido() == correo2.getContenido())
                                        return true;
    return false;
}

bool Correo::operator !=(Correo &correo2)
{
    if (this->getFechaEnvio() != correo2.getFechaEnvio())
        return true;
    if (this->getHoraEnvio() != correo2.getHoraEnvio())
        return true;
    if (this->getRem() != correo2.getRem())
        return true;
    if (this->getDestinatario() != correo2.getDestinatario())
        return true;
    if (this->getCopiaCarbon() != correo2.getCopiaCarbon())
        return true;
    if (this->getCopiaCarbonCiega() != correo2.getCopiaCarbonCiega())
        return true;
    if (this->getAsunto() != correo2.getAsunto())
        return true;
    if (this->getContenido() != correo2.getContenido())
        return true;
    return false;
}
