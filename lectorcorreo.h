#ifndef LECTORCORREO_H
#define LECTORCORREO_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "correo.h"
#include "ldl.h"

#if defined(_WIN64) || defined(_WIN64)
    #define CLEAR std::system("cls")
#else
    #define CLEAR std::system("clear")
#endif

using namespace std;

class LectorCorreo
{
public:
    LectorCorreo();
    virtual ~LectorCorreo();

    void menu();
    void crear();
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
    size_t m_correos;

    enum OPC
    {
        CREAR = '1',
        LEER_ID,
        LEER_REM,
        MOD_ID,
        MOD_REM,
        SALIR
    };
};

#endif // LECTORCORREO_H
