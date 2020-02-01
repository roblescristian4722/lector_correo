#include "lectorcorreo.h"

LectorCorreo::LectorCorreo()
{
    m_correos = 0;
}

LectorCorreo::~LectorCorreo()
{
}

void LectorCorreo::menu()
{
    CLEAR;
    char opc;
    fstream entrada("datos.bin", ios::binary | ios::in);
    if (!entrada.is_open())
        cout << " Nota: Aún no se ha creado archivo binario, ejecute la opción \"crear\"" << endl;
    entrada.seekg(0);
    entrada.read((char*)&m_correos, sizeof(size_t));
    entrada.close();
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
                crear();
            break;

            case LEER_ID:
                size_t id;
                cout << " Ingrese el ID del correo a buscar: ";
                cin >> id;
                leer(id);
                cin.ignore();
            break;

            case LEER_REM:
            break;

            case MOD_ID:
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

void LectorCorreo::crear()
{
    ofstream archivo("datos.bin", ios::out | ios::binary);
    if (!archivo.is_open())
        cout << "Error en el achivo" << endl;

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
    cin.getline(contenido, 500);
    correoTmp.setFechaEnvio(ctime(&fecha));
    correoTmp.setIdentificador(m_correos + 1);
    correoTmp.setRem(rem);
    correoTmp.setAsunto(asunto);
    correoTmp.setContenido(contenido);
    correoTmp.setCopiaCarbon(copiaCarbon);
    correoTmp.setDestinatario(dest);
    correoTmp.setCopiaCarbonCiega(copiaCarbonCiega);

    archivo.seekp(0);
    ++m_correos;
    archivo.write((char*)&m_correos, sizeof(size_t));

    long pos = sizeof(size_t) + (m_correos - 1) * sizeof(Correo);
    archivo.seekp(pos);

    archivo.write((char*)&correoTmp, sizeof(Correo));

    archivo.close();
}

const Correo &LectorCorreo::leer(size_t id)
{
    if (id > m_correos || !id)
        cout << endl
             << " El identificador no corresponde a ningún correo" << endl;
    else
    {
        ifstream archivo("datos.bin", ios::in | ios::binary);
        if (!archivo.is_open())
            cout << "Error en el achivo" << endl;

        Correo correoTmp;

        long pos = sizeof(size_t) + (id - 1) * sizeof(Correo);
        archivo.seekg(pos);
        archivo.read((char*)&correoTmp, sizeof(Correo));

        archivo.close();

        cout << endl
             << " ID: " << correoTmp.getIdentificador() << endl
             << " Asunto: " << correoTmp.getAsunto() << endl
             << " Remitente: " << correoTmp.getRem() << endl
             << " Destinatario: " << correoTmp.getDestinatario() << endl
             /*<< " Fecha: " << correoTmp.getFechaEnvio() << endl*/
             << " CC: " << correoTmp.getCopiaCarbon() << endl
             << " CCCiega: " << correoTmp.getCopiaCarbonCiega() << endl
             << " Contenido: " << correoTmp.getContenido() << endl;
    }
}

const Correo &LectorCorreo::leer(const char* remitente)
{

}

void LectorCorreo::modificar(size_t id)
{

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
