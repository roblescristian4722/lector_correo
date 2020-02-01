#include "lectorcorreo.h"

LectorCorreo::LectorCorreo()
{
    m_correos = 0;
    Correo tmp;
    fstream entrada("datos.bin", ios::binary | ios::in);
    if (!entrada.is_open())
    {
        cout << " Nota: Aún no se ha creado archivo binario, ejecute la opción \"crear\"" << endl
             << " Creando archivo binario..." << endl;
        entrada.open("datos.bin", ios::binary | ios::out);
    }
    entrada.seekg(0);
    entrada.read((char*)&m_correos, sizeof(size_t));
    for (size_t i = 0; i < m_correos; i++)
    {
        long pos = sizeof(size_t) + i * sizeof(Correo);
        entrada.seekg(pos);
        entrada.read((char*)&tmp, sizeof(Correo));
        m_correosLista.push_back(tmp);
    }
    entrada.close();
}

LectorCorreo::~LectorCorreo()
{
}

void LectorCorreo::menu()
{
    CLEAR;
    char opc;
    do
    {
        cout << " Bienvenido, eliga la opción a ejecutar" << endl
             << " Correos ingresados: " << m_correos << endl
             << char(CREAR) << ") Crear correo" << endl
             << char(LEER_ID) << ") Buscar correo por ID" << endl
             << char(LEER_REM) << ") Buscar correo por remitente" << endl
             << char(MOD_ID) << ") Modificar correo (buscar por ID)" << endl
             << char(MOD_REM) << ") Modificar correo (buscar por remitente)" << endl
             << char(SALIR) << ") Salir" << endl
             << "Opción: ";
        cin >> opc;
        cin.ignore();
        CLEAR;
        switch (opc)
        {
            case CREAR:
            {

                // Correo temporal que guardará los datos y los escribirá
                // al archivo binario
                Correo correoTmp;
                char dest[50];
                char rem[50];
                char copiaCarbon[100];
                char copiaCarbonCiega[100];
                char asunto[200];
                char contenido[500];

                // Se obtiene la fecha del sistema
                auto now = chrono::system_clock::now();
                auto fecha = chrono::system_clock::to_time_t(now);

                // Se guardan datos al correo temporal
                cout << " Introduzca la siguiente información:" << endl << endl
                     << " Destinatario: ";
                cin.getline(dest, 50);
                cout << " Remitente: ";
                cin.getline(rem, 50);
                cout << " Copia Carbón (opcional): ";
                cin.getline(copiaCarbon, 100);
                cout << " Copia Carbón Ciega (opcinal): ";
                cin.getline(copiaCarbonCiega, 100);
                cout << " Asunto: ";
                cin.getline(asunto, 200);
                cout << " Contenido: ";
                cin.getline(contenido, 500, '~');
                correoTmp.setFechaEnvio(ctime(&fecha));
                correoTmp.setIdentificador(m_correos + 1);
                correoTmp.setRem(rem);
                correoTmp.setAsunto(asunto);
                correoTmp.setContenido(contenido);
                correoTmp.setCopiaCarbon(copiaCarbon);
                correoTmp.setDestinatario(dest);
                correoTmp.setCopiaCarbonCiega(copiaCarbonCiega);
                crear(correoTmp);
            }
            break;

            case LEER_ID:
            {
                size_t id;
                Correo mostrar;
                cout << " Ingrese el ID del correo a buscar: ";
                cin >> id;
                if (id > m_correos || !id)
                    cout << endl
                         << " El identificador no corresponde a ningún correo" << endl;
                else
                {
                    mostrar = leer(id);
                    cout << endl
                         << " ID: " << mostrar.getIdentificador() << endl
                         << " Remitente: " << mostrar.getRem() << endl
                         << " Destinatario: " << mostrar.getDestinatario() << endl
                         /*<< " Fecha: " << correoTmp.getFechaEnvio() << endl*/
                         << " CC: " << mostrar.getCopiaCarbon() << endl
                         << " CCCiega: " << mostrar.getCopiaCarbonCiega() << endl
                         << " Asunto: " << mostrar.getAsunto() << endl
                         << " Contenido: " << mostrar.getContenido() << endl;
                }
                cin.ignore();
            }
            break;

            case LEER_REM:
            break;

            case MOD_ID:
                cout << " Ingrese el id del correo a modificar: ";
                size_t id;
                cin >> id;
                if (id > m_correos || !id)
                    cout << endl
                         << " El identificador no corresponde a ningún correo" << endl;
                else
                {
                    Correo correoTmp;
                    auto now = chrono::system_clock::now();
                    auto fecha = chrono::system_clock::to_time_t(now);
                    char dest[50];
                    char rem[50];
                    char copiaCarbon[100];
                    char copiaCarbonCiega[100];
                    char asunto[200];
                    char contenido[500];

                    cout << " Ingrese los siguientes datos" << endl << endl
                         << " Destinatario: ";
                    cin.ignore();
                    cin.getline(dest, 50);
                    cout << " Remitente: ";
                    cin.getline(rem, 50);
                    cout << " Copia Carbón (opcional): ";
                    cin.getline(copiaCarbon, 100);
                    cout << " Copia Carbón Ciega (opcinal): ";
                    cin.getline(copiaCarbonCiega, 100);
                    cout << " Asunto: ";
                    cin.getline(asunto, 200);
                    cout << " Contenido: ";
                    cin.getline(contenido, 500, '~');

                    correoTmp.setFechaEnvio(ctime(&fecha));
                    correoTmp.setIdentificador(id);
                    correoTmp.setRem(rem);
                    correoTmp.setAsunto(asunto);
                    correoTmp.setContenido(contenido);
                    correoTmp.setCopiaCarbon(copiaCarbon);
                    correoTmp.setDestinatario(dest);
                    correoTmp.setCopiaCarbonCiega(copiaCarbonCiega);
                    
                    modificar(id, correoTmp);
                    cout << endl
                         << " Los cambios se han realizado con éxito" << endl;
                }
                cin.ignore();
            break;

            case MOD_REM:
            break;

            case SALIR:
            return;

            default:
            break;
        }
        cout << endl
             << "---------------------------------" << endl
             << " Presione ENTER para continuar" << endl;
        cin.get();
        CLEAR;
    }while (opc != SALIR);
}

void LectorCorreo::crear(Correo &correo)
{
    fstream archivo("datos.bin", ios::out | ios::binary | ios::in);
    if (!archivo.is_open())
        cout << "Error en el achivo" << endl;

    // Se guarda en los primeros 8 bytes del archivo la
    // cantidad de correos almacenados
    ++m_correos;
    archivo.seekp(0);
    archivo.write((char*)&m_correos, sizeof(size_t));

    // Se elige la posición en la que se escribirá el correo
    // A esta se le suman los bytes del size_t para que no sobre
    // escriba el campo del contador
    long pos = sizeof(size_t) + (m_correos - 1) * sizeof(Correo);
    archivo.seekp(pos);
    // Se almacena el correo nuevo
    archivo.write((char*)&correo, sizeof(Correo));
    m_correosLista.push_back(correo);

    archivo.close();
}

 const Correo &LectorCorreo::leer(size_t id)
{
    return m_correosLista[id - 1];
}

const Correo &LectorCorreo::leer(const char* remitente)
{

}

void LectorCorreo::modificar(size_t id, Correo& correo)
{
    fstream archivo("datos.bin", ios::in | ios::out | ios::binary);
    if (!archivo.is_open())
        cout << " Error en el archivo de entrada" << endl;
    
    long pos = sizeof(size_t) + (id - 1) * sizeof(Correo);
    archivo.seekp(pos);

    archivo.write((char*)&correo, sizeof(Correo));
    archivo.close();
    m_correosLista.erase(id - 1);
    m_correosLista.insert(correo, id - 1);

}

void LectorCorreo::modificar(const char *remitente)
{
    cout << remitente << endl;
}


// Setters y Getters
size_t LectorCorreo::getCorreos() const
{
    return m_correos;
}

void LectorCorreo::setCorreos(const size_t &correos)
{
    m_correos = correos;
}
