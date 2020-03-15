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
#include "avl_tree.h"

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

    struct Indice
    {
        Indice(){}
        Indice(const char* id, long pos) : referencia(pos)
        {
            strcpy(llave, id);
        }

        bool operator < (const Indice &other)
        {
            return atol(this->llave) < atol(other.llave);
        }

        bool operator > (const Indice &other)
        {
            return atol(this->llave) > atol(other.llave);
        }

        bool operator == (const long llave)
        {
            return atol(this->llave) == llave;
        }

        bool operator == (const Indice &other)
        {
            return atol(this->llave) == atol(other.llave);
        }

        char llave[10];
        long referencia;
    };

    void menu();
    void crear(Correo* tmp);
    Correo leer(unsigned long id);
    void leer(LDL<unsigned long>* ids);
    void leer_rem(LDL<unsigned long>* lista, const char* rem);
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

    // Búsqueda eficiente con árboles
    Correo* leerIndicePrimario(AVLTree<LectorCorreo::Indice>& arbol);

private:
};

#endif // LECTORCORREO_H
