#ifndef INDICES_H
#define INDICES_H

#include <iostream>
#include <cstring>
#include <string>
#include "lsl.h"
using namespace std;

//// INDICE PRIMARIO ////
struct IndicePrimario
{
public:
    IndicePrimario(){}
    IndicePrimario(const char* id, long pos);
    ~IndicePrimario(){}

    /// SOBRECARGA DE OPERADORES ///
    bool operator < (const IndicePrimario &other);
    bool operator > (const IndicePrimario &other);
    bool operator == (const IndicePrimario &other);
    bool operator == (const long llave);
    friend ostream& operator << (ostream& os, const IndicePrimario& other)
    {
        os << other.getLlave();
        return os;
    }

    /// GETTERS ///
    long getReferencia() const;
    string getLlave() const;

    /// SETTERS ///
    void setReferencia(long referencia);
    void setLlave(const string llave);

private:
    char m_llave[10];
    long m_referencia;
};

//// INDICE SECUNDARIO ////
class IndiceSecundario
{
public:
    IndiceSecundario();
    IndiceSecundario(const char* llave);
    ~IndiceSecundario();

    /// SOBRECARGA DE OPERADORES ///
    bool operator < (const IndiceSecundario &other);
    bool operator > (const IndiceSecundario &other);
    bool operator > (const string &llave);
    bool operator == (const IndiceSecundario &other);
    void operator = (IndiceSecundario &other);
    bool operator == (const string llave);
    friend ostream& operator << (ostream& os, const IndiceSecundario& other)
    {
        os << other.getLlave();
        return os;
    }

    /// GETTERS ///
    string getLlave() const;
    LSL<IndicePrimario>*& getReferencia();

    /// SETTERS ///
    void setLlave(const string llave);

private:
    char m_llave[50];
    LSL<IndicePrimario> *m_referencia;
};

#endif // INDICES_H
