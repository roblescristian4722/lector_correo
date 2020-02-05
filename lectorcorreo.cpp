#include "lectorcorreo.h"

LectorCorreo::LectorCorreo()
{
    // Por defecto el contador de correos se iguala a 0
    // y cada id a false
    //m_correos.correos = 0;
    //for (size_t i = 0; i < 10; i++)
      //  m_correos.posiciones[i] = false;
    // Se abre un archivo binario en modo de entrada
    fstream entrada("datos.bin", ios::binary | ios::in);
    if (!entrada.is_open())
    {
        entrada.open("datos.bin", ios::binary | ios::out);
        entrada.close();
    }
    else
    {
        entrada.seekg(0);
        entrada.read((char*)&m_correos, sizeof(Datos));
        entrada.close();
    }
}

LectorCorreo::~LectorCorreo()
{
}

void LectorCorreo::crear(Correo* correo)
{
    fstream archivo("datos.bin", ios::out | ios::binary | ios::in);
    if (!archivo.is_open())
        cout << "Error en el achivo" << endl;

    // Se elige la posición en la que se escribirá el correo
    // A esta se le suman los bytes del size_t para que no sobre
    // escriba el campo del contador
    long pos = (atoll(correo->getIdentificador()) - 1) * sizeof(Correo);
    archivo.seekp(pos);
    // Se almacena el correo nuevo
    archivo.write((char*)correo, sizeof(Correo));
    archivo.close();
}

 Correo* LectorCorreo::leer(size_t id)
{
    Correo* tmp = new Correo;
    fstream archivo("datos.bin", ios::in | ios::out | ios::binary);
    if (!archivo.is_open())
        cout << " Error al abrir el archivo" << endl;
    long pos = (id - 1) * sizeof(Correo);
    archivo.seekg(pos);
    archivo.read((char*)tmp, sizeof(Correo));
    return tmp;
}

void LectorCorreo::modificar(size_t id, Correo* correo)
{
    fstream archivo("datos.bin", ios::in | ios::out | ios::binary);
    if (!archivo.is_open())
        cout << " Error en el archivo de entrada" << endl;
    
    long pos = (id - 1) * sizeof(Correo);
    archivo.seekp(pos);

    archivo.write((char*)correo, sizeof(Correo));
    archivo.close();
    delete correo;
}

bool LectorCorreo::getPosicion(int index)
{
    return m_correos.posiciones[index];
}

bool* LectorCorreo::getPosicion()
{
    return m_correos.posiciones;
}
