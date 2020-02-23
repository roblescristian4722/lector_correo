#ifndef CORREO_H
#define CORREO_H

#include <iostream>
#include <chrono>
#include <string.h>
using namespace std;

class Correo
{
public:
    Correo();
    virtual ~Correo();

    // Getters
    char *getIdentificador() const;
    char *getHoraEnvio() const;
    char *getContenido() const;
    char *getAsunto() const;
    char *getCopiaCarbon() const;
    char *getCopiaCarbonCiega() const;
    char *getDestinatario() const;
    char *getRem() const;
    char *getFechaEnvio() const;

    // Setters
    void setHoraEnvio(const char *horaEnvio);
    void setIdentificador(const char* identificador);
    void setContenido(const char *contenido);
    void setAsunto(const char *asunto);
    void setCopiaCarbonCiega(const char *copiaCarbonCiega);
    void setCopiaCarbon(const char *copiaCarbon);
    void setDestinatario(const char *destinatario);
    void setRem(const char *value);
    void setFechaEnvio(const char *fechaEnvio);

    // Sobrecarga de operadores
    bool operator ==(Correo& correo2);
    bool operator !=(Correo& correo2);

private:
    char m_identificador[11];
    char m_horaEnvio[9];
    char m_fechaEnvio[11];
    char m_destinatario[50];
    char m_rem[50];
    char m_copiaCarbon[100];
    char m_copiaCarbonCiega[100];
    char m_asunto[200];
    char m_contenido[500];
};

#endif // CORREO_H
