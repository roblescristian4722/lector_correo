#include "indices.h"


IndicePrimario::IndicePrimario(const char *id, long pos)
{
    m_referencia = pos;
    setLlave(id);
}

IndiceSecundario::IndiceSecundario()
{}

IndiceSecundario::IndiceSecundario(const char *llave)
{ setLlave(llave); }

IndiceSecundario::~IndiceSecundario()
{ m_referencia.clear(); }


/// SOBRECARGA DE OPERADORES ///
bool IndicePrimario::operator <(const IndicePrimario &other)
{ return atol(this->getLlave().c_str()) < atol(other.getLlave().c_str()); }

bool IndicePrimario::operator >(const IndicePrimario &other)
{ return atol(this->getLlave().c_str()) > atol(other.getLlave().c_str()); }

bool IndicePrimario::operator ==(const IndicePrimario &other)
{ return atol(this->getLlave().c_str()) == atol(other.getLlave().c_str()); }

bool IndicePrimario::operator ==(const long llave)
{ return atol(this->getLlave().c_str()) == llave; }

bool IndiceSecundario::operator <(const IndiceSecundario &other)
{ return this->getLlave() < other.getLlave(); }

bool IndiceSecundario::operator >(const IndiceSecundario &other)
{ return this->getLlave() > other.getLlave(); }

bool IndiceSecundario::operator >(const string &llave)
{ return this->getLlave() > llave; }

bool IndiceSecundario::operator ==(const IndiceSecundario &other)
{ return this->getLlave() == other.getLlave(); }

IndiceSecundario& IndiceSecundario::operator =(IndiceSecundario &other)
{
    this->setLlave(other.getLlave());
    this->m_referencia.clear();
    for(size_t i = 0; i < other.m_referencia.size(); ++i)
        this->m_referencia.push_back(other.m_referencia[i]);
    return *this;
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

LSL<IndicePrimario>& IndiceSecundario::getReferencia()
{ return m_referencia; }

/// SETTERS ///
void IndicePrimario::setReferencia(long referencia)
{ m_referencia = referencia; }

void IndicePrimario::setLlave(const string llave)
{ strcpy(m_llave, llave.c_str()); }

void IndiceSecundario::setLlave(const string llave)
{ strcpy(m_llave, llave.c_str()); }
