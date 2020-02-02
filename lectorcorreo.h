#ifndef LECTORCORREO_H
#define LECTORCORREO_H

#include <iostream>
#include <fstream>
#include <ctime>
#include "correo.h"
#include "ldl.h"

#if defined(_WIN32) || defined(_WIN64)
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
    void crear(Correo* tmp, size_t id);
    Correo leer(size_t id);
    const Correo& leer(const char* remitente);
    void modificar(size_t id, Correo* correo);
    void modificar(const char* remitente);
    Correo& obtenerID(size_t id);
    /*void eliminar(size_t id);
    void eliminar(const char* remitente);
    void exportar(size_t id);
    void exportar(const char* remitente);
    void importar();
    void exportar();*/

private:
    enum OPC
    {
        CREAR = '1',
        LEER_ID,
        LEER_REM,
        MOD_ID,
        MOD_REM,
        SALIR
    };

    struct Datos
    {
        size_t correos;
        bool posiciones[10];
    };

    Datos m_correos;
};

#endif // LECTORCORREO_H
