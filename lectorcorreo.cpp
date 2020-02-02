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
        // En caso de que falle la lectura del archivo se crea uno
        cout << " Nota: Aún no se ha creado archivo binario, ejecute la opción \"crear\"" << endl
             << " Creando archivo binario..." << endl;
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

void LectorCorreo::menu()
{
    CLEAR;
    char opc;
    do
    {
        cout << " Bienvenido, eliga la opción a ejecutar" << endl
             << " Correos ingresados: " << m_correos.correos << endl
             << " " << char(CREAR) << ") Crear correo" << endl
             << " " << char(LEER_ID) << ") Buscar correo por ID" << endl
             << " " << char(LEER_REM) << ") Buscar correo por remitente" << endl
             << " " << char(MOD_ID) << ") Modificar correo (buscar por ID)" << endl
             << " " << char(MOD_REM) << ") Modificar correo (buscar por remitente)" << endl
             << " " << char(SALIR) << ") Salir" << endl
             << " Opción: ";
        cin >> opc;
        cin.ignore();
        CLEAR;
        switch (opc)
        {
            case CREAR:
            {
                if (m_correos.correos < 10)
                {
                    // Correo temporal que guardará los datos y los escribirá
                    // al archivo binario
                    Correo *correoTmp = new Correo;
                    char dest[50];
                    char rem[50];
                    char copiaCarbon[100];
                    char copiaCarbonCiega[100];
                    char asunto[200];
                    char contenido[500];
                    char fechaEnvio[11];
                    char horaEnvio[9];
                    size_t id = 0;
                    bool correoVal = false;

                    do
                    {
                        CLEAR;
                        cout << " Ingrese un ID para el correo (entre 1 y 10): ";
                        cin >> id;
                        if (id > 0 && id < 11)
                            if (!m_correos.posiciones[id - 1])
                                correoVal = true;
                            else
                            {
                                cout << " Error: el id ya está en uso. Intente modificarlo desde el menú" << endl
                                     << " Presione ENTER para continuar" << endl;
                                cin.ignore();cin.get();
                            }
                        else
                        {
                            cout << " Error: id fuera de rango" << endl
                                 << " presione ENTER para continuar" << endl;
                            cin.ignore();cin.get();
                        }
                    } while (!correoVal);
                    
                    cin.ignore();
                    // Se guardan datos al correo temporal
                    cout << endl
                         << " Introduzca la siguiente información:" << endl << endl
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
                    cout << " Contenido (NOTA: escriba un caracter \"~\" en la parte en la que desee" << endl
                        << " terminar de escribir el contenido del mensaje):" << endl << " ";
                    cin.getline(contenido, 500, '~');

                    // Se obtiene la fecha del sistema
                    time_t now = time(0);
                    tm * time = localtime(&now);
                    snprintf(fechaEnvio, sizeof(fechaEnvio), "%s/%s/%s", to_string(time->tm_mday).c_str(),
                            to_string(time->tm_mon + 1).c_str(), to_string(time->tm_year + 1900).c_str());

                    snprintf(horaEnvio, sizeof(horaEnvio), "%d:%d:%d", time->tm_hour, time->tm_min, time->tm_sec);

                    // Se introducen los atributos al objeto con setters
                    correoTmp->setIdentificador(id);
                    correoTmp->setFechaEnvio(fechaEnvio);
                    correoTmp->setHoraEnvio(horaEnvio);
                    correoTmp->setRem(rem);
                    correoTmp->setAsunto(asunto);
                    correoTmp->setContenido(contenido);
                    correoTmp->setCopiaCarbon(copiaCarbon);
                    correoTmp->setDestinatario(dest);
                    correoTmp->setCopiaCarbonCiega(copiaCarbonCiega);
                    
                    // Se guarda el objeto en el archivo biario en la siguiente clase
                    crear(correoTmp, id);
                }
                else
                    cout << "Lo sentimos, la bandeja está llena" << endl;
            }
            break;

            case LEER_ID:
            {
                size_t id;
                Correo* mostrar = new Correo;
                cout << " Ingrese el ID del correo a buscar: ";
                cin >> id;
                if (id < 1 || id > 10)
                    cout << endl
                         << " El identificador está fuera del rango (1 - 10)" << endl;
                else if (!m_correos.posiciones[id - 1])
                    cout << endl
                         << " El identificador aún no está en uso, primero cree un correo con este id"
                         << endl;
                else
                {
                    *mostrar = leer(id);
                    cout << endl
                         << " ID: " << mostrar->getIdentificador() << endl
                         << " Remitente: " << mostrar->getRem() << endl
                         << " Destinatario: " << mostrar->getDestinatario() << endl
                         << " Fecha de envío: " << mostrar->getFechaEnvio() << endl
                         << " Hora de envío: " << mostrar->getHoraEnvio() << endl
                         << " CC: " << mostrar->getCopiaCarbon() << endl
                         << " CCCiega: " << mostrar->getCopiaCarbonCiega() << endl
                         << " Asunto: " << mostrar->getAsunto() << endl
                         << " Contenido: " << mostrar->getContenido() << endl;
                    delete mostrar;
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
                if (id < 1 || id > 10)
                    cout << endl
                         << " El identificador está fuera del rango (1 - 10)" << endl;
                else if (!m_correos.posiciones[id - 1])
                    cout << endl
                         << " El identificador aún no está en uso, primero cree un correo con este id"
                         << endl;
                else
                {   
                    // Variables temporales para copiar los datos de la clase y mostrarlos
                    Correo* correoTmp = new Correo;
                    *correoTmp = leer(id);
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
                    cout << " Contenido (NOTA: escriba un caracter \"~\" en la parte en la que desee" << endl
                         << " terminar de escribir el contenido del mensaje):" << endl << " ";
                    cin.getline(contenido, 500, '~');

                    correoTmp->setIdentificador(id);
                    correoTmp->setRem(rem);
                    correoTmp->setAsunto(asunto);
                    correoTmp->setContenido(contenido);
                    correoTmp->setCopiaCarbon(copiaCarbon);
                    correoTmp->setDestinatario(dest);
                    correoTmp->setCopiaCarbonCiega(copiaCarbonCiega);
                    
                    cout << "dafasdfasf" << endl;cin.get();
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
    delete correo;
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

const Correo &LectorCorreo::leer(const char* remitente)
{
    // Aún sin implementar
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

void LectorCorreo::modificar(const char *remitente)
{
    // Sin implementar
}