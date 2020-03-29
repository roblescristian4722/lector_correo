#include "indices.h"


IndicePrimario::IndicePrimario(const char *id, long pos)
{
    m_referencia = pos;
    setLlave(id);
}

IndiceSecundario::IndiceSecundario()
{}

IndiceSecundario::IndiceSecundario(const char *llave)
{
    setLlave(llave);
    m_referencia = new LSL<IndicePrimario>;
}

IndiceSecundario::~IndiceSecundario()
{ delete m_referencia; }


/// SOBRECARGA DE OPERADORES ///
bool IndicePrimario::operator <(const IndicePrimario &other)
{ return stol(this->getLlave()) < stol(other.getLlave()); }

bool IndicePrimario::operator >(const IndicePrimario &other)
{ return stol(this->getLlave()) > stol(other.getLlave()); }

bool IndicePrimario::operator ==(const IndicePrimario &other)
{ return stol(this->getLlave()) == stol(other.getLlave()); }

bool IndicePrimario::operator ==(const long llave)
{ return stol(this->getLlave()) == llave; }

bool IndiceSecundario::operator <(const IndiceSecundario &other)
{ return this->getLlave() < other.getLlave(); }

bool IndiceSecundario::operator >(const IndiceSecundario &other)
{ return this->getLlave() > other.getLlave(); }

bool IndiceSecundario::operator >(const string &llave)
{ return this->getLlave() > llave; }

bool IndiceSecundario::operator ==(const IndiceSecundario &other)
{ return this->getLlave() == other.getLlave(); }

void IndiceSecundario::operator =(IndiceSecundario &other)
{
    this->setLlave(other.getLlave());
    this->getReferencia()->clear();
    for(size_t i = 0; i < other.getReferencia()->size(); ++i)
        this->getReferencia()->push_back((*other.getReferencia())[i]);
}

bool IndiceSecundario::operator ==(const string llave)
{ return this->getLlave() == llave; }

/// GETTERS ///
long IndicePrimario::getReferencia() const
{ return m_referencia; }

string IndicePrimario::getLlave() const
{ return m_llave; }

string IndiceSecundario::getLlave() const
{ return m_llave; }

LSL<IndicePrimario>*& IndiceSecundario::getReferencia()
{ return m_referencia; }

/// SETTERS ///
void IndicePrimario::setReferencia(long referencia)
{ m_referencia = referencia; }

void IndicePrimario::setLlave(const string llave)
{ strcpy(m_llave, llave.c_str()); }

void IndiceSecundario::setLlave(const string llave)
{ strcpy(m_llave, llave.c_str()); }
