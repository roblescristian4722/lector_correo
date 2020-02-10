#include "lectorcorreo.h"

LectorCorreo::LectorCorreo()
{
    // Se crea un archivo nuevo en caso de que aún no exista
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
{}

void LectorCorreo::eliminar(size_t id)
{
    Correo tmp;
    tmp.setIdentificador("");
    fstream archivo("datos.bin", ios::out | ios::in | ios::binary);
    if (!archivo.is_open())
        cout << "Error en el archivo" << endl;
    else
    {
        unsigned long pos = (id - 1) * sizeof(Correo);
        archivo.seekp(pos);
        archivo.write((char*)&tmp, sizeof(Correo));
    }
}

void LectorCorreo::crear(Correo* correo)
{
    fstream archivo("datos.bin", ios::out | ios::binary | ios::in);
    if (!archivo.is_open())
        cout << "Error en el achivo" << endl;
    else
    {
        /*
         Se elige la posición en la que se escribirá el correo
         con ayuda del id
        */
        long pos = (atoll(correo->getIdentificador()) - 1) * sizeof(Correo);
        archivo.seekp(pos);

        // Se almacena el correo nuevo y se cierra el achivo
        archivo.write((char*)correo, sizeof(Correo));
        archivo.close();
    }
}

 Correo* LectorCorreo::leer(size_t id)
{
     /*
      * Se crea un Correo temporal en memoria dinámica
      * que guardará los datos almacenados en el archivo
      * de texto en una posición determinada y luego se
      * pasará dicho correo a las ventanas
    */
    Correo* tmp = new Correo;
    /*
     * Se abre el archivo en modo de lectura y escritura al mismo
     * tiempo para evitar que se sobrescriban los datos del archivo
     * de texto
    */
    fstream archivo("datos.bin", ios::in | ios::out | ios::binary);
    if (!archivo.is_open())
        cout << " Error al abrir el archivo" << endl;
    /*
     * Se calcula la posición en la que se leerá, luego se pone el
     * apuntador en esa posición con seekg, luego se guardan los datos
     * en la variable temporal y el puntero que guarda su dirección se
     * retorna
    */
    long pos = (id - 1) * sizeof(Correo);
    archivo.seekg(pos);
    archivo.read((char*)tmp, sizeof(Correo));
    return tmp;
}

void LectorCorreo::leer(LDL<Correo>* lista)
{
    Correo tmp;
    fstream archivo("datos.bin", ios::out | ios::in | ios::binary);
    archivo.seekg(ios::beg);
    for (unsigned long i = 0; !archivo.eof(); i++)
    {
        unsigned long pos = i * sizeof(Correo);
        archivo.seekg(pos);
        archivo.read((char*)&tmp, sizeof(Correo));
        if (atol(tmp.getIdentificador()) == i + 1)
            lista->push_back(tmp);
    }
    archivo.close();
}

void LectorCorreo::leerRem(LDL<Correo>* lista, const char* rem)
{
    Correo tmp;
    fstream archivo("datos.bin", ios::out | ios::in | ios::binary);
    archivo.seekg(ios::beg);
    for (unsigned long i = 0; !archivo.eof(); i++)
    {
        unsigned long pos = i * sizeof(Correo);
        archivo.seekg(pos);
        archivo.read((char*)&tmp, sizeof(Correo));
        if (!strcmp(rem, tmp.getRem()))
            lista->push_back(tmp);
    }
    archivo.close();
}

bool LectorCorreo::getPosicion(int index)
{
    return m_correos.posiciones[index];
}

bool* LectorCorreo::getPosicion()
{
    return m_correos.posiciones;
}
