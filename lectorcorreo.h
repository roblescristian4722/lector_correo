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
#include "hash_map.h"

#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR std::system("cls")
#else
    #define CLEAR std::system("clear")
#endif

using namespace std;

class LectorCorreo
{
public:
    LectorCorreo(AVLTreePrimario *indices, AVLTreePrimario *paginados, AVLTreeSecundario *rem,
                 AVLTreeSecundario *des, HashMap<string, Vector<string>>* mapRem);
    virtual ~LectorCorreo();

    void menu();

    // guardar índices en archivo
    void guardar_indices();

    // Cargar datos de archivo
    void cargar_archivo_indices(bool indicesPaginados = false);
    void cargar_archivo_datos();

    // Operaciones básicas
    void crear(Correo* tmp, bool modificar = false, bool hash = false);
    Correo leer(const char* id);
    Correo leer(long pos);
    void leer(LSL<long>& ids);
    void leer_rem(LSL<long>& lista, const char* rem);
    void modificar(long id, Correo& correo);
    void eliminar(long id, bool paginado = false, bool hash = false);

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

    // Cargar índices en memoria
    void cargar_map();

private:
    AVLTreePrimario* m_indices;
    AVLTreePrimario* m_paginados;
    AVLTreeSecundario* m_rem;
    AVLTreeSecundario* m_des;
    HashMap<string, Vector<string>> *m_mapRem;
};

#endif // LECTORCORREO_H
