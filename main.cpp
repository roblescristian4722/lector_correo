#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

struct Test
{
    char telefono[10];
    char nombre[10];
    char apellido[10];
};

void writeTest(const char* tel, const char* nom, const char* ape, unsigned long nrr = 1);
Test readTest(unsigned long nrr);

int main()
{
    Test t1;
    //writeTest("123123", "crisscros", "roblas");
    t1 = readTest(1);
    cout << t1.nombre << " " << t1.apellido << " " << t1.telefono << endl;
    return 0;
}

void writeTest(const char* tel, const char* nom, const char* ape, unsigned long nrr)
{
    long pos = (nrr - 1) * sizeof(Test);
    Test* tmp = new Test();

    ofstream salida("datos.bin", ios::out | ios::binary | ios::trunc);
    if (!salida.is_open())
        cout << "Error en el archivo de salida" << endl;
    salida.seekp(pos);

    strcpy(tmp->nombre, nom);
    strcpy(tmp->telefono, tel);
    strcpy(tmp->apellido, ape);

    salida.write((char*)tmp, sizeof(Test));

    salida.close();
}

Test readTest(unsigned long nrr)
{
    long pos = (nrr - 1) * sizeof(Test);
    Test* tmp = new Test;

    ifstream entrada("datos.bin", ios::in | ios::binary);
    if (!entrada.is_open())
        cout << "Error en el archivo de entrada" << endl;

    entrada.seekg(pos);
    entrada.read((char*)tmp, sizeof(Test));

    entrada.close();
    return *tmp;
}
