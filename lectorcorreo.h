#ifndef LECTORCORREO_H
#define LECTORCORREO_H

#include <iostream>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <string>
#include "correo.h"
#include "ldl.h"
#include "vector.h"

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
    void crear(Correo* tmp);
    Correo* leer(unsigned long id);
    void leer(LDL<Correo>* lista);
    void leer_rem(LDL<Correo>* lista, const char* rem);
    void modificar(unsigned long id, Correo* correo);
    void eliminar(unsigned long id);

    // Copia de seguridad (CSV)
    void crear_copia_seguridad();
    void modificar_copia(Correo* correo, LDL<string> idRegistrados);
    void validar_comillas(Correo* correo);
    void eliminar_copia_seguridad(string id, LDL<string> idRegistrados);

    // Copia de seguridad de propietario
    void crear_copia_propietario();
    bool modificar_copia_propietario(Correo* correo);
    bool eliminar_copia_propietario(long id);

    // Cargar en RAM
    void leerRAM(Vector<Correo> *vec);

private:
};

#endif // LECTORCORREO_H
