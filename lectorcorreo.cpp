#include "lectorcorreo.h"

LectorCorreo::LectorCorreo()
{
    // Por defecto se iguala 0 al contador de correos
    m_correos.correos = 0;
    for (size_t i = 0; i < 10; i++)
        m_correos.posiciones[i] = false;
    // Correo temporal que se utilizará para obtener todos los correos del binario
    Correo tmp;
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

void LectorCorreo::crear(Correo* correo, size_t id)
{
    fstream archivo("datos.bin", ios::out | ios::binary | ios::in);
    if (!archivo.is_open())
        cout << "Error en el achivo" << endl;

    // Se guarda en los primeros 8 bytes del archivo la
    // cantidad de correos almacenados
    ++m_correos.correos;
    m_correos.posiciones[id - 1] = true;
    archivo.seekp(0);
    archivo.write((char*)&m_correos, sizeof(Datos));

    // Se elige la posición en la que se escribirá el correo
    // A esta se le suman los bytes del size_t para que no sobre
    // escriba el campo del contador
    long pos = sizeof(Datos) + (id - 1) * sizeof(Correo);
    archivo.seekp(pos);
    // Se almacena el correo nuevo
    archivo.write((char*)correo, sizeof(Correo));
    archivo.close();
}

 Correo LectorCorreo::leer(size_t id)
{
    Correo tmp;
    fstream archivo("datos.bin", ios::in | ios::out | ios::binary);
    if (!archivo.is_open())
        cout << " Error al abrir el archivo" << endl;
    long pos = sizeof(Datos) + (id - 1) * sizeof(Correo);
    archivo.seekg(pos);
    archivo.read((char*)&tmp, sizeof(Correo));
    return tmp;
}

void LectorCorreo::modificar(size_t id, Correo* correo)
{
    fstream archivo("datos.bin", ios::in | ios::out | ios::binary);
    if (!archivo.is_open())
        cout << " Error en el archivo de entrada" << endl;
    
    long pos = sizeof(Datos) + (id - 1) * sizeof(Correo);
    archivo.seekp(pos);

    archivo.write((char*)correo, sizeof(Correo));
    archivo.close();
    delete correo;
}

bool LectorCorreo::getPosicion(int index)
{
    return m_correos.posiciones[index];
}
