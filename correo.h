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
    size_t getIdentificador() const;
    size_t getHoraEnvio() const;
    char *getContenido() const;
    char *getAsunto() const;
    char *getCopiaCarbon() const;
    char *getCopiaCarbonCiega() const;
    char *getDestinatario() const;
    char *getRem() const;
    char *getFechaEnvio() const;

    // Setters
    void setHoraEnvio(const size_t &horaEnvio);
    void setIdentificador(const size_t &identificador);
    void setContenido(const char *contenido);
    void setAsunto(const char *asunto);
    void setCopiaCarbonCiega(const char *copiaCarbonCiega);
    void setCopiaCarbon(const char *copiaCarbon);
    void setDestinatario(const char *destinatario);
    void setRem(const char *value);
    void setFechaEnvio(const char *fechaEnvio);

private:
    size_t m_identificador;
    size_t m_horaEnvio;
    char m_fechaEnvio[50];
    char m_destinatario[50];
    char m_rem[50];
    char m_copiaCarbon[100];
    char m_copiaCarbonCiega[100];
    char m_asunto[200];
    char m_contenido[500];
};

#endif // CORREO_H