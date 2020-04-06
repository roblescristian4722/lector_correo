#ifndef LSL_H
#define LSL_H

#include<iostream>
#include<stdexcept>
using namespace std;

template<typename T>
class LSL
{
public:
    LSL()
    {
        listSize = 0;
        listFront = nullptr;
        listBack = nullptr;
    }
    ~LSL()
    {
        clear();
    }

    // STATUS
    bool empty() const;
    size_t size() const;

    // ADD
    void push_front(const T& element);
    void push_back(const T& element);
    void insert(size_t position, const T& element);

    // Back - Front
    const T& front() const; 
    const T& back() const;

    //  Remove
    void pop_front();
    void pop_back();
    void erase(size_t position);
    void clear();
    void remove(const T& value);

    //operator overloading
    T& operator [](size_t index); 

private:
    struct NodoLSL
    {
        T dato;
        NodoLSL* siguiente;
        // sig = nullptr representa un valo por omisión
        NodoLSL(const T& elem, NodoLSL* sig = nullptr)
        {
            dato = elem;
            siguiente = sig;
        }
    };
    size_t listSize;
    NodoLSL* listFront;
    NodoLSL* listBack;
};

template <typename T>
bool LSL<T>::empty() const
{
    return listSize == 0;
}

template <typename T>
size_t LSL<T>::size() const
{
    return listSize;
}

template <typename T>
void LSL<T>::push_front(const T &element)
{
    if (empty())
    {
        listFront = new NodoLSL(element);
        listBack = listFront;
    }
    else
    {
        NodoLSL* tmp = new NodoLSL(element, listFront);
        listFront = tmp;
    }
    ++ listSize;
}

template <typename T>
void LSL<T>::push_back(const T &element)
{
    if (empty())
    {
        listFront = new NodoLSL(element);
        listBack = listFront;
    }
    else
    {
        NodoLSL* tmp = new NodoLSL(element);
        listBack->siguiente = tmp;
        listBack = tmp;
    }
    ++listSize;
}

template<typename T>
const T& LSL<T>::front() const
{
    if (empty())
        throw range_error("Trying to front() on an empty list");
    return listFront->dato;
}

template<typename T>
const T& LSL<T>::back() const
{
    if (empty())
        throw range_error("Trying to back() on an empty list");
    return listBack->dato;
}

template<typename T>
void LSL<T>::pop_front()
{
    if (empty())
        throw range_error("Trying to pop_front() on an empty list");
    
    NodoLSL* tmp = listFront;
    listFront = listFront->siguiente;
    delete tmp;
    tmp = nullptr;
    --listSize;
}

template<typename T>
void LSL<T>::pop_back()
{
    if (empty())
        throw range_error("Trying to pop_back() on an empty list");
    NodoLSL* tmp = listFront;
    while (tmp->siguiente != nullptr && tmp->siguiente != listBack)
        tmp = tmp->siguiente;
    delete tmp->siguiente;
    tmp->siguiente = nullptr;
    listBack = tmp;
    listBack->siguiente = nullptr;
    --listSize;
}

template<typename T>
void LSL<T>::insert(size_t position, const T &element)
{
    if (position > listSize)
        throw range_error("insert() in non valid position");
    if (!position)
        push_front(element);
    else if (position == listSize)
        push_back(element);
    else
    {
        NodoLSL* temp = listFront;
        for (size_t i(0); i < position - 1; ++i)
            temp = temp->siguiente;
        NodoLSL* nuevo = new NodoLSL(element, temp->siguiente);
        temp->siguiente = nuevo;
        ++listSize;
    }
}

template<typename T>
void LSL<T>::erase(size_t position)
{
    if (empty())
        throw range_error("erase() on empty list");
    if (position >= listSize)
        throw range_error("erase on non valid position");
    else if (!position)
        pop_front();
    else if(position == listSize - 1)
        pop_back();
    else
    {
        NodoLSL* temp = listFront;
        for (size_t i(0); i < position - 1; ++i)
            temp = temp->siguiente;
        NodoLSL* eliminar = temp->siguiente;
        temp->siguiente = eliminar->siguiente;
        delete eliminar;
        eliminar = nullptr;
        --listSize;
    }
}

template<typename T>
void LSL<T>::clear()
{
    for (size_t i(0); i < listSize; ++i)
        pop_front();
    listSize = 0;
    listFront = nullptr;
    listBack  = nullptr;
}

template<typename T>
void LSL<T>::remove(const T& value)
{
    if (empty())
        throw range_error("remove() on empty list");
    NodoLSL* temp = listFront;
    size_t i = 0;
    T dato;
    while(temp != nullptr)
    {
        dato = temp->dato;
        temp = temp->siguiente;
        if (dato == value)
        {
            erase(i);
            --i;
        }
        ++i;
    }
}

template<typename T>
T& LSL<T>::operator [](size_t index)
{
    if (empty())
        throw range_error("[] in empty list");
    if (index >= listSize)
        throw range_error("[] in non valid position");
    NodoLSL* temp = listFront;
    for(size_t i(0); i < index; ++i)
        temp = temp->siguiente;
    return temp->dato;
}

#endif // LSL_H
