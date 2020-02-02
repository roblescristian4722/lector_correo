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
    void modificar(size_t id, Correo* correo);
    Correo& obtenerID(size_t id);

    bool getPosicion(int index);
    bool* getPosicion();

private:
    struct Datos
    {
        size_t correos;
        bool posiciones[10];
    };

    // Estructura que gestiona los id usados
    // y la cantidad de correos ingresados
    Datos m_correos;
};

#endif // LECTORCORREO_H
