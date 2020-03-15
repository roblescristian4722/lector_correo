#include "lectorcorreo.h"
#define TOTAL_CAMPOS 9

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

void LectorCorreo::eliminar(long id)
{
    Correo tmp;
    tmp.setIdentificador("");
    fstream archivo("datos.bin", ios::out | ios::in | ios::binary);
    if (!archivo.is_open())
        cout << "Error en el archivo" << endl;
    else
    {
        long pos = (id - 1) * long(sizeof(Correo));
        archivo.seekp(pos);
        archivo.write((char*)&tmp, long(sizeof(Correo)));
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
        long pos = (atoll(correo->getIdentificador()) - 1) * long(sizeof(Correo));
        archivo.seekp(pos);

        // Se almacena el correo nuevo y se cierra el achivo
        archivo.write((char*)correo, long(sizeof(Correo)));
        archivo.close();
    }
}

Correo LectorCorreo::leer(const char* id)
{
     /*
      * Se crea un Correo temporal en memoria dinámica
      * que guardará los datos almacenados en el archivo
      * de texto en una posición determinada y luego se
      * pasará dicho correo a las ventanas
    */
    Correo tmp;
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
    else
    {
        long pos = (atol(id) - 1) * long(sizeof(Correo));
        archivo.seekg(pos);
        archivo.read((char*)&tmp, long(sizeof(Correo)));
        return tmp;
    }
}

Correo* LectorCorreo::leer(long pos)
{
    Correo* tmp = new Correo;
    ifstream archivo("datos.bin", ios::in | ios::binary);
    if (!archivo.is_open())
        cout << "Error en el archivo de entrada" << endl;
    else
    {
        archivo.seekg(pos);
        archivo.read((char*)tmp, long(sizeof(Correo)));
        return tmp;
    }
}

void LectorCorreo::leer(LDL<unsigned int>* ids)
{
    Correo tmp;
    fstream archivo("datos.bin", ios::out | ios::in | ios::binary);
    archivo.seekg(ios::beg);
    for (long i = 0; !archivo.eof(); i++)
    {
        long pos = i * long(sizeof(Correo));
        archivo.seekg(pos);
        archivo.read((char*)&tmp, long(sizeof(Correo)));
        if (atol(tmp.getIdentificador()) == i + 1)
            ids->push_back(atoi(tmp.getIdentificador()));
    }
    archivo.close();
}

void LectorCorreo::leer_rem(LDL<unsigned int>* lista, const char* rem)
{
    Correo correoTmp;
    string strTmp;
    long i;
    fstream archivo("datos.bin", ios::out | ios::in | ios::binary);

    if (!archivo.is_open())
        cout << "error en archivo binario" << endl;

    archivo.seekg(ios::beg);
    for (i = 0; !archivo.eof(); i++)
    {
        long pos = i * long(sizeof(Correo));
        archivo.seekg(pos);
        archivo.read((char*)&correoTmp, long(sizeof(Correo)));
        strTmp = correoTmp.getRem();
        if (strTmp == rem)
            lista->push_back(atol(correoTmp.getIdentificador()));
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

    for (long i = 0; !binario.eof(); i++)
    {

        long pos = i * long(sizeof(Correo));
        binario.seekg(pos);
        binario.read((char*)&correoTmp, long(sizeof(Correo)));

        if (atol(correoTmp.getIdentificador()) == i + 1)
        {
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

void LectorCorreo::crear_copia_propietario()
{
    Correo correoTmp;
    char tam;
    fstream bin("datos.bin", ios::in | ios::out | ios::binary);
    fstream prop("respaldo.dat", ios::binary | ios::out);
    if (!bin.is_open())
        cout << "Error en el archivo de entrada" << endl;
    else
    {
        while(!bin.eof())
        {
            // se lee del binario
            bin.read((char*)&correoTmp, sizeof (Correo));

            if (bin.eof())
                break;

            // Se escribe en la copia de propietario
            // ID
            tam = char(strlen(correoTmp.getIdentificador()));
            // Si el ID está vacío entonces no se guarda
            if (tam)
            {
                prop.write((char*)&tam, sizeof(tam));
                for (int i = 0; i < int(tam); ++i)
                    prop.write((char*)correoTmp.getIdentificador() + i, sizeof(char));

                // Fecha
                tam = char(strlen(correoTmp.getFechaEnvio()));
                prop.write((char*)&tam, sizeof(tam));
                for (int i = 0; i < tam; i++)
                    prop.write((char*)correoTmp.getFechaEnvio() + i, sizeof(char));

                // Hora
                tam = char(strlen(correoTmp.getHoraEnvio()));
                prop.write((char*)&tam, sizeof(tam));
                for (int i = 0; i < tam; i++)
                    prop.write((char*)correoTmp.getHoraEnvio() + i, sizeof(char));

                // Remitente
                tam = char(strlen(correoTmp.getRem()));
                prop.write((char*)&tam, sizeof(tam));
                for (int i = 0; i < tam; i++)
                    prop.write((char*)correoTmp.getRem() + i, sizeof(char));

                // Destinatario
                tam = char(strlen(correoTmp.getDestinatario()));
                prop.write((char*)&tam, sizeof(tam));
                for (int i = 0; i < tam; i++)
                    prop.write((char*)correoTmp.getDestinatario() + i, sizeof(char));

                // CC
                tam = char(strlen(correoTmp.getCopiaCarbon()));
                prop.write((char*)&tam, sizeof(tam));
                for (int i = 0; i < tam; i++)
                    prop.write((char*)correoTmp.getCopiaCarbon() + i, sizeof(char));

                // CCC
                tam = char(strlen(correoTmp.getCopiaCarbonCiega()));
                prop.write((char*)&tam, sizeof(tam));
                for (int i = 0; i < tam; i++)
                    prop.write((char*)correoTmp.getCopiaCarbonCiega() + i, sizeof(char));

                // Asunto
                tam = char(strlen(correoTmp.getAsunto()));
                prop.write((char*)&tam, sizeof(tam));
                for (int i = 0; i < tam; i++)
                    prop.write((char*)correoTmp.getAsunto() + i, sizeof(char));

                // Contenido
                tam = char(strlen(correoTmp.getContenido()));
                prop.write((char*)&tam, sizeof(tam));
                for (int i = 0; i < tam; i++)
                    prop.write((char*)correoTmp.getContenido() + i, sizeof(char));
            }
        }
        bin.close();
    }
}

bool LectorCorreo::modificar_copia_propietario(Correo* correo)
{
    char aux;
    char auxString[500];
    char tam = 1;
    long cont = 0;
    int i = 0;
    bool found = false;
    bool match = false;
    fstream prop("respaldo.dat", ios::in | ios::binary);
    fstream tmp("respaldo.tmp", ios::out | ios::binary);
    if (!prop.is_open())
        cout << "Error en el archivo de entrada" << endl;
    else
    {
        while(!prop.eof())
        {
            prop.read((char*)&tam, sizeof(tam));

            if (prop.eof())
                break;

            for (i = 0; i < int(tam); ++i)
            {
                prop.get(aux);
                auxString[i] = aux;
            }

            auxString[i] = '\0';
            ++cont;

            if (!match || (match && (cont == 2 || cont == 3)))
            {
                tmp.write((char*)&tam, sizeof(tam));
                for (i = 0; i < int(tam); ++i)
                    tmp << auxString[i];
                // En caso de encontrar el ID se activa ésta bandera
                if (!strcmp(auxString, correo->getIdentificador()) && cont == 1)
                    match = true;
            }
            else if (match)
            {
                switch(cont)
                {
                    case 4:
                        tam = char(strlen(correo->getRem()));
                        tmp.write((char*)&tam, sizeof(tam));
                        for (i = 0; i < int(tam); ++i)
                            tmp << correo->getRem()[i];
                    break;
                    case 5:
                        tam = char(strlen(correo->getDestinatario()));
                        tmp.write((char*)&tam, sizeof(tam));
                        for (i = 0; i < int(tam); ++i)
                            tmp << correo->getDestinatario()[i];
                    break;
                    case 6:
                        tam = char(strlen(correo->getCopiaCarbon()));
                        tmp.write((char*)&tam, sizeof(tam));
                        for (i = 0; i < int(tam); ++i)
                            tmp << correo->getCopiaCarbon()[i];
                    break;
                    case 7:
                        tam = char(strlen(correo->getCopiaCarbonCiega()));
                        tmp.write((char*)&tam, sizeof(tam));
                        for (i = 0; i < int(tam); ++i)
                            tmp << correo->getCopiaCarbonCiega()[i];
                    break;
                    case 8:
                        tam = char(strlen(correo->getAsunto()));
                        tmp.write((char*)&tam, sizeof(tam));
                        for (i = 0; i < int(tam); ++i)
                            tmp << correo->getAsunto()[i];
                    break;
                    case 9:
                        tam = char(strlen(correo->getContenido()));
                        tmp.write((char*)&tam, sizeof(tam));
                        for (i = 0; i < int(tam); ++i)
                            tmp << correo->getContenido()[i];
                        match = false;
                        found = true;
                    break;
                }
            }
            cont %= TOTAL_CAMPOS;
        }
        prop.close();
        tmp.close();
    }
    remove("respaldo.dat");
    rename("respaldo.tmp", "respaldo.dat");
    return found;
}

bool LectorCorreo::eliminar_copia_propietario(long id)
{
    bool encontrado = false;
    bool borrar = false;
    int cont = 0;
    int i;
    char tam;
    char aux;
    char auxString[500] = "\0";

    fstream tmp("respaldo.tmp", ios::out | ios::binary);
    fstream prop("respaldo.dat", ios::in | ios::binary);
    if (!prop.is_open())
        cout << "Error en el archivo de entrada" << endl;
    else
    {
        while (!prop.eof())
        {
            prop.read((char*)&tam, sizeof(tam));

            if (prop.eof())
                break;

            for (i = 0; i < int(tam); ++i)
            {
                prop.get(aux);
                auxString[i] = aux;
            }
            auxString[i] = '\0';
            ++cont;
            if (cont == 1 && atoi(auxString) == id)
            {
                encontrado = true;
                borrar = true;
            }
            else if (!borrar)
            {
                tmp.write((char*)&tam, sizeof(tam));
                for (i = 0; i < int(tam); ++i)
                    tmp << auxString[i];
            }

            if (cont == TOTAL_CAMPOS && borrar)
                borrar = false;

            cont %= TOTAL_CAMPOS;
        }
        prop.close();
        tmp.close();
        remove("respaldo.dat");
        rename("respaldo.tmp", "respaldo.dat");
    }
    return encontrado;
}

void LectorCorreo::leerRAM(Vector<Correo> *vec)
{
    Correo tmpCorreo;
    fstream archivo("datos.bin", ios::out | ios::in | ios::binary);
    archivo.seekg(ios::beg);
    for (long i = 0; !archivo.eof(); i++)
    {
        long pos = i * long(sizeof(Correo));
        archivo.seekg(pos);
        archivo.read((char*)&tmpCorreo, long(sizeof(Correo)));
        if (atol(tmpCorreo.getIdentificador()) == i + 1)
            vec->push_back(tmpCorreo);
    }
    archivo.close();
}

Correo *LectorCorreo::leerIndicePrimario(AVLTree<LectorCorreo::Indice>& arbol)
{
    Correo tmpCorreo;
    fstream bin("datos.bin", ios::in | ios::binary);
    for(long i = 1; !bin.eof(); ++i)
    {
        bin.read((char*)&tmpCorreo, long(sizeof(Correo)));
        if (atol(tmpCorreo.getIdentificador()) == i)
        {
            long pos = bin.tellg();
            LectorCorreo::Indice tmpIndice(tmpCorreo.getIdentificador(), pos - long(sizeof(Correo) ));
            arbol.insertData(tmpIndice);
        }
    }
}
