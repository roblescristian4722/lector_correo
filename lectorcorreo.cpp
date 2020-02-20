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
    Correo correoTmp;
    string strTmp;
    unsigned long long i;
    fstream archivo("datos.bin", ios::out | ios::in | ios::binary);
    if (!archivo.is_open())
        cout << "error en archivo binario" << endl;
    archivo.seekg(ios::beg);
    for (i = 0; !archivo.eof(); i++)
    {
        unsigned long long pos = i * sizeof(Correo);
        archivo.seekg(pos);
        archivo.read((char*)&correoTmp, sizeof(Correo));
        strTmp = correoTmp.getRem();
        if (strTmp == rem)
            lista->push_back(correoTmp);
    }
}

void LectorCorreo::crearCopiaSeguridad()
{
    Correo correoTmp;
    char contenidoTmp[500];
    fstream binario("datos.bin", ios::in | ios::binary);
    if (!binario.is_open())
        cout << "error en binario" << endl;
    ofstream csv("respaldo.csv", ios::out | ios::binary);
    if (!csv.is_open())
        cout << "error en csv" << endl;

    csv << "ID," << "Fecha de envío, " << "Hora de envío,"
        << "Remitente," << "Destinatario," << "Copia Carbón,"
        << "Copia Carbón Ciega," << "Asunto," << "Contenido"
        << endl;

    for (unsigned long i = 0; !binario.eof(); i++)
    {
        char contenidoTmp[500];
        char asuntoTmp[200];
        bool asuntoComillas = false;
        bool contenidoComillas = false;
        unsigned long pos = i * sizeof(Correo);
        binario.seekg(pos);
        binario.read((char*)&correoTmp, sizeof(Correo));

        if (atol(correoTmp.getIdentificador()) == i + 1)
        {
            int i = 0;
            int matchesContenido = 0;

            // Se validan las comillas dobles en contenido
            for (i; !(*(correoTmp.getContenido() + i) == '\0'); i++)
            {
                if (*(correoTmp.getContenido() + i) == '"')
                {
                    contenidoTmp[i + matchesContenido] = *(correoTmp.getContenido() + i);
                    ++matchesContenido;
                    contenidoTmp[i + matchesContenido] = '"';
                    asuntoComillas = true;
                }
                else
                    contenidoTmp[i + matchesContenido] = *(correoTmp.getContenido() + i);
                if (*(correoTmp.getContenido() + i) == ','
                         || *(correoTmp.getContenido() + i) == '\n')
                    contenidoComillas = true;
            }
            contenidoTmp[i + matchesContenido] = '\0';

            // Se validan las comillas dobles en el asunto
            i = 0;
            int matchesAsunto = 0;
            for (i; !(*(correoTmp.getAsunto() + i) == '\0'); i++)
            {
                if (*(correoTmp.getAsunto() + i) == '"')
                {
                    asuntoTmp[i + matchesAsunto] = *(correoTmp.getAsunto() + i);
                    ++matchesAsunto;
                    asuntoTmp[i + matchesAsunto] = '"';
                    asuntoComillas = true;
                }
                else
                    asuntoTmp[i + matchesAsunto] = *(correoTmp.getAsunto() + i);
                if (*(correoTmp.getAsunto() + i) == ','
                    || *(correoTmp.getAsunto() + i) == '\n')
                    asuntoComillas = true;
            }
            asuntoTmp[i + matchesAsunto] = '\0';

            // Se guarda todo en el csv
            csv << correoTmp.getIdentificador() << ','
                << correoTmp.getFechaEnvio() << ','
                << correoTmp.getHoraEnvio() << ','
                << correoTmp.getRem() << ','
                << correoTmp.getDestinatario() << ','
                << correoTmp.getCopiaCarbon() << ','
                << correoTmp.getCopiaCarbonCiega() << ',';

            if (asuntoComillas)
                csv << '"' << asuntoTmp << '"' << ',';
            else
                csv << asuntoTmp << ',';

            if (contenidoComillas)
                csv << '"' << contenidoTmp << '"' << endl;
            else
                csv << contenidoTmp << endl;
        }
    }
    binario.close();
    csv.close();
}

bool LectorCorreo::getPosicion(int index)
{
    return m_correos.posiciones[index];
}

bool* LectorCorreo::getPosicion()
{
    return m_correos.posiciones;
}
