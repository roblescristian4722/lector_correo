#ifndef LECTORCORREO_H
#define LECTORCORREO_H

#include <iostream>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <string>
#include "correo.h"
#include "lsl.h"
#include "vector.h"
#include "avl_tree_primario.h"
#include "indices.h"

#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR std::system("cls")
#else
    #define CLEAR std::system("clear")
#endif

using namespace std;

class LectorCorreo
{
public:
    LectorCorreo(AVLTreePrimario *indices, AVLTreeSecundario *rem, AVLTreeSecundario *des);

    virtual ~LectorCorreo();

    void menu();
    void crear(Correo* tmp, bool modificar = false);
    Correo leer(const char* id);
    Correo leer(long pos);
    void leer(LSL<unsigned int>& ids);
    void leer_rem(LSL<unsigned int>& lista, const char* rem);
    void modificar(long id, Correo& correo);
    void eliminar(long id, AVLTreePrimario* indices);

    // Copia de seguridad (CSV)
    void crear_copia_seguridad();
    void modificar_copia(Correo &correo, LSL<string> &idRegistrados);
    void validar_comillas(Correo &correo);
    void eliminar_copia_seguridad(string id, LSL<string> idRegistrados);

    // Copia de seguridad de propietario
    void crear_copia_propietario();
    bool modificar_copia_propietario(Correo &correo);
    bool eliminar_copia_propietario(long id);

    // Cargar en RAM
    void leerRAM(Vector<Correo> &vec);

private:
    AVLTreePrimario* m_indices;
    AVLTreeSecundario* m_rem;
    AVLTreeSecundario* m_des;
};

#endif // LECTORCORREO_H
