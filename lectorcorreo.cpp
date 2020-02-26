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
}

LectorCorreo::~LectorCorreo()
{}

void LectorCorreo::eliminar(unsigned long id)
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

 Correo* LectorCorreo::leer(unsigned long id)
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

void LectorCorreo::leer_rem(LDL<Correo>* lista, const char* rem)
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

void LectorCorreo::crear_copia_seguridad()
{
    Correo correoTmp;
    fstream binario("datos.bin", ios::in | ios::binary);
    if (!binario.is_open())
        cout << "error en binario" << endl;
    ofstream csv("respaldo.csv", ios::out | ios::binary);
    if (!csv.is_open())
        cout << "error en csv" << endl;

    csv << "ID," << "Fecha de envío," << "Hora de envío,"
        << "Remitente," << "Destinatario," << "Copia Carbón,"
        << "Copia Carbón Ciega," << "Asunto," << "Contenido"
        << endl;

    for (unsigned long i = 0; !binario.eof(); i++)
    {

        unsigned long pos = i * sizeof(Correo);
        binario.seekg(pos);
        binario.read((char*)&correoTmp, sizeof(Correo));

        if (atol(correoTmp.getIdentificador()) == i + 1)
        {
            int i = 0;
            int matchesContenido = 0;

            validar_comillas(&correoTmp);

            // Se guarda todo en el csv
            csv << correoTmp.getIdentificador() << ','
                << correoTmp.getFechaEnvio() << ','
                << correoTmp.getHoraEnvio() << ','
                << correoTmp.getRem() << ','
                << correoTmp.getDestinatario() << ','
                << correoTmp.getCopiaCarbon() << ','
                << correoTmp.getCopiaCarbonCiega() << ','
                << correoTmp.getAsunto() << ','
                << correoTmp.getContenido() << '\n';
        }
    }
    binario.close();
    csv.close();
}

void LectorCorreo::modificar_copia(Correo* correo, LDL<string> idRegistrados)
{
    string aux;
    string auxID = "";
    fstream csv("respaldo.csv", ios::in);
    fstream tmp("respaldo.tmp", ios::out);

    if (!tmp.is_open())
        cout << "No abierto" << endl;

    while (!csv.eof())
    {
        getline(csv, aux);
        auxID = "";
        for (int i = 0; aux[i] != ','; ++i)
            auxID += aux[i];

        if (auxID == correo->getIdentificador())
        {
            validar_comillas(correo);
            tmp << correo->getIdentificador() << ','
                << correo->getFechaEnvio() << ','
                << correo->getHoraEnvio() << ','
                << correo->getRem() << ','
                << correo->getDestinatario() << ','
                << correo->getCopiaCarbon() << ','
                << correo->getCopiaCarbonCiega() << ','
                << correo->getAsunto() << ','
                << correo->getContenido() << '\n';
            idRegistrados.pop_front();
            if (idRegistrados.empty())
            {
                csv.seekg(ios::end);
                break;
            }
            do
            {
                getline(csv, aux);
                auxID = "";
                for (int i = 0; aux[i] != ','; ++i)
                    auxID += aux[i];
            }while(auxID != idRegistrados.front());
            tmp << aux << '\n';
        }
        else if (auxID == idRegistrados.front())
        {
            idRegistrados.pop_front();
            tmp << aux << '\n';
        }
        else
            tmp << aux << '\n';
    }
    csv.close();
    tmp.close();

    remove("respaldo.csv");
    rename("respaldo.tmp", "respaldo.csv");
}

void LectorCorreo::validar_comillas(Correo *correo)
{
    char contenidoTmp[500];
    char asuntoTmp[200];
    bool asuntoComillas = false;
    bool contenidoComillas = false;
    int i = 0;
    int matchesContenido = 0;

    // Se validan las comillas dobles en contenido
    for (i; *(correo->getContenido() + i) != '\0'; i++)
    {
        if (*(correo->getContenido() + i) == '"')
        {
            contenidoTmp[i + matchesContenido] = *(correo->getContenido() + i);
            ++matchesContenido;
            contenidoTmp[i + matchesContenido] = '"';
            asuntoComillas = true;
        }
        else
            contenidoTmp[i + matchesContenido] = *(correo->getContenido() + i);
        if (*(correo->getContenido() + i) == ','
                 || *(correo->getContenido() + i) == '\n')
            contenidoComillas = true;
    }
    contenidoTmp[i + matchesContenido] = '\0';
    correo->setContenido(contenidoTmp);

    // Se validan las comillas dobles en el asunto
    i = 0;
    int matchesAsunto = 0;
    for (i; *(correo->getAsunto() + i) != '\0'; i++)
    {
        if (*(correo->getAsunto() + i) == '"')
        {
            asuntoTmp[i + matchesAsunto] = *(correo->getAsunto() + i);
            ++matchesAsunto;
            asuntoTmp[i + matchesAsunto] = '"';
            asuntoComillas = true;
        }
        else
            asuntoTmp[i + matchesAsunto] = *(correo->getAsunto() + i);
        if (*(correo->getAsunto() + i) == ','
            || *(correo->getAsunto() + i) == '\n')
            asuntoComillas = true;
    }

    asuntoTmp[i + matchesAsunto] = '\0';
    if (asuntoComillas)
    {
        string asuntoComillas = "\"";
        asuntoComillas += asuntoTmp;
        asuntoComillas += "\"";
        correo->setAsunto(asuntoComillas.c_str());
    }
    else
        correo->setAsunto(asuntoTmp);

    if (contenidoComillas)
    {
        string contenidoComillas = "\"";
        contenidoComillas += contenidoTmp;
        contenidoComillas += "\"";
        correo->setContenido(contenidoComillas.c_str());
    }
    else
        correo->setContenido(contenidoTmp);
}

void LectorCorreo::eliminar_copia_seguridad(string id, LDL<string> idRegistrados)
{
    fstream csv("respaldo.csv", ios::in);
    fstream tmp("respaldo.tmp", ios::out);
    string aux;
    string auxID;
    bool eof = false;

    if (!tmp.is_open())
        cout << "No abierto" << endl;

    while (!csv.eof())
    {
        getline(csv, aux);
        auxID = "";
        for (int i = 0; aux[i] != ','; ++i)
            auxID += aux[i];

        if (auxID == id)
        {
            /* Si se encuentra el ID en el archivo se
             * elimina de la lista de id's y no se ecribe
             * nada en el tmp hasta encontrar otro ID
            */
            idRegistrados.pop_front();
            if (idRegistrados.size())
            {
                cout << "asdf" << endl;
                do
                {
                    /*
                     * Una vez que se encuentra otro ID
                     * se sale del ciclo y se escribe en
                     * el archivo
                     */

                    getline(csv, aux);
                    auxID = "";
                    for (int i = 0; aux[i] != ','; ++i)
                        auxID += aux[i];
                }while(auxID != idRegistrados.front());
                tmp << aux << '\n';
            }
            else
            {
                csv.seekg(ios::end);
                break;
            }
        }
        /*
         * Cualquier ID que se encuentre se borrará
         * de la lista de ID's y además se escribirá
         * la línea en el archivo
        */
        else if (auxID == idRegistrados.front())
        {
            idRegistrados.pop_front();
            tmp << aux << '\n';
        }
        /*
         * Cualquier otra línea se va a escribir
         * en el archivo de texto
        */
        else
            tmp << aux << '\n';
    }
    csv.close();
    tmp.close();

    remove("respaldo.csv");
    rename("respaldo.tmp", "respaldo.csv");
}

