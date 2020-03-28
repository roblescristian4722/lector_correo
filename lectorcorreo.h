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
    struct Indice
    {
        Indice(){}
        Indice(const char* id, long pos) : referencia(pos)
        { strcpy(llave, id); }

        bool operator < (const Indice &other)
        { return atol(this->llave) < atol(other.llave); }

        bool operator > (const Indice &other)
        { return atol(this->llave) > atol(other.llave); }

        friend ostream& operator << (ostream& os, const Indice& other)
        {
            os << other.llave;
            return os;
        }

        bool operator == (const long llave)
        { return atol(this->llave) == llave; }

        bool operator == (const Indice &other)
        { return atol(this->llave) == atol(other.llave); }

        char llave[10];
        long referencia;
    };

    LectorCorreo(AVLTree<LectorCorreo::Indice> *indices);

    virtual ~LectorCorreo();

    void menu();
    void crear(Correo* tmp, AVLTree<LectorCorreo::Indice>* indices, bool modificar = false);
    Correo leer(const char* id);
    Correo leer(long pos);
    void leer(LDL<unsigned int>& ids);
    void leer_rem(LDL<unsigned int>& lista, const char* rem);
    void modificar(long id, Correo& correo);
    void eliminar(long id, AVLTree<LectorCorreo::Indice>* indices);

    // Copia de seguridad (CSV)
    void crear_copia_seguridad();
    void modificar_copia(Correo &correo, LDL<string> idRegistrados);
    void validar_comillas(Correo &correo);
    void eliminar_copia_seguridad(string id, LDL<string> idRegistrados);

    // Copia de seguridad de propietario
    void crear_copia_propietario();
    bool modificar_copia_propietario(Correo &correo);
    bool eliminar_copia_propietario(long id);

    // Cargar en RAM
    void leerRAM(Vector<Correo> &vec);

private:
    AVLTree<LectorCorreo::Indice>* m_indices;
};

#endif // LECTORCORREO_H
