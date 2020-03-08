#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Vector
{
public:
    Vector()
    {
        m_vectorCapacity = 1;
        m_vectorSize = 0;
        m_container = new T[m_vectorCapacity];
    }
    Vector(const Vector<T>& other)
    {
        m_vectorSize = other.m_vectorSize;
        m_vectorCapacity = other.m_vectorCapacity;
        m_container = new T[m_vectorCapacity];
        for (int i = 0; i < other.m_vectorSize; ++i)
            m_container[i] = other[i];
    }
    virtual ~Vector()
    {
        clear();
    }

    // STATUS
    size_t size() const;
    size_t capacity() const;

    // ADD
    void push_back(const T& element);
    void insert(size_t position, const T& element);

    // REMOVE
    void pop_back();
    void erase(size_t position);
    void clear();
    void resize(size_t size, const T &element = 0);
    void resize();

    // POSITION
    const T& at(size_t position) const;

    // SOBRECARGA DE OPERADORES
    T& operator [](size_t index) const;
    const Vector<T>& operator =(const Vector<T>& other);

private:
    T* m_container;
    size_t m_vectorSize;
    size_t m_vectorCapacity;
};

// STATUS
template<typename T>
size_t Vector<T>::size() const
{
    return m_vectorSize;
}

template <typename T>
size_t Vector<T>::capacity() const
{
    return m_vectorCapacity;
}

// ADD
template <typename T>
void Vector<T>::push_back(const T& element)
{
    resize();
    m_container[m_vectorSize] = element;
    ++m_vectorSize;
}

template <typename T>
void Vector<T>::insert(size_t position, const T& element)
{
    if (position > m_vectorSize)
        throw range_error("");
    if (position == m_vectorSize)
        push_back(element);
    else
    {
        resize();
        for (int i = m_vectorSize + 1; i > int(position); --i)
            m_container[i] = m_container[i - 1];
        m_container[position] = element;
        ++m_vectorSize;
    }
}

// REMOVE
template <typename T>
void Vector<T>::pop_back()
{
    if (!m_vectorSize)
        throw range_error("pop_back on empty vector");

    --m_vectorSize;
}

template <typename T>
void Vector<T>::resize(size_t size, const T& element)
{
    if (size < m_vectorSize)
        while (size < m_vectorSize)
            pop_back();
    else if (size > m_vectorSize)
        while (size > m_vectorSize)
            push_back(element);
}

template <typename T>
void Vector<T>::erase(size_t position)
{
    if (position >= m_vectorSize)
        throw range_error("erase(size_t position) on non valid position");
    if (position == m_vectorSize - 1)
        pop_back();
    else
    {
        for (int i = position; i < m_vectorSize - 1; ++i)
            m_container[i] = m_container[i + 1];
        --m_vectorSize;
    }
}

template <typename T>
void Vector<T>::clear()
{
    for (int i = 0; m_vectorSize != 0; ++i)
        pop_back();
}

// POSITION
template <typename T>
const T& Vector<T>::at(size_t position) const
{
    if (position >= m_vectorSize)
        throw range_error("at(size_t position) on non valid position");
    return m_container[position];
}


// SOBRECARGA DE OPERADORES
template <typename T>
T& Vector<T>::operator[](size_t index) const
{
    if (index >= m_vectorSize)
        throw range_error("operator[size_t index] on non valid index");
    return m_container[index];
}

template <typename T>
const Vector<T>& Vector<T>::operator =(const Vector<T>& other)
{
    clear();
    m_vectorSize = other.m_vectorSize;
    m_vectorCapacity = other.m_vectorCapacity;
    m_container = new T[m_vectorCapacity];
    for (size_t i = 0; i < other.m_vectorSize; ++i)
        m_container[i] = other[i];
    return *this;
}

template <typename T>
void Vector<T>::resize()
{
    if (m_vectorSize == m_vectorCapacity)
    {
        m_vectorCapacity *= 2;
        T *temp = new T[m_vectorCapacity];

        for (int i = 0; i < int(m_vectorSize); i++)
            temp[i] = m_container[i];

        delete[] m_container;
        m_container = temp;
        temp = nullptr;
    }
}

#endif
