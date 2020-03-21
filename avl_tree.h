#ifndef AVL_TREE
#define AVL_TREE

#include <iostream>
#include <stdexcept>
#include <fstream>
#include "lectorcorreo.h"
#include "vector.h"
using namespace std;

template<typename T>
class AVLTree
{
public:
    struct AVLTreeNode
    {
        T* dataPtr;
        AVLTreeNode* right;
        AVLTreeNode* left;

        AVLTreeNode( T& data)
        {
            dataPtr = new T(data);
            right = nullptr;
            left = nullptr;
        }
        ~AVLTreeNode()
        {
            delete dataPtr;
            dataPtr = nullptr;
        }
    };

    AVLTree() : m_root(nullptr){}
    ~AVLTree()
    {}

    // MODIFY DATA
    void insertData(T& data);
    void removeData(T& data);
    void removeNode(AVLTreeNode*& node);
    void removeAll();

    // PARSE
    void writeFileInOrder();
    void parseInOrder(Vector<T> &vec);
    void parsePreOrder(Vector<T> &vec);
    void parsePostOrder(Vector<T> &vec);

    // PROPERTIES
    bool isLeaf();
    bool isLeaf(AVLTreeNode*& node);
    unsigned int height();

    // GET AVL DATA
    AVLTreeNode*& findData(T& data);
    AVLTreeNode*& lowestData();
    AVLTreeNode*& highestData();

private:
    AVLTreeNode* m_root;

    // MODIFY DATA
    void insertData(T& data, AVLTreeNode*& node);
    void removeAll(AVLTreeNode*& node);

    // PARSE
    void parsePreOrder(AVLTreeNode*& node, Vector<T> &vec);
    void parsePostOrder(AVLTreeNode*& node, Vector<T> &vec);
    void parseInOrder(AVLTreeNode*& node, Vector<T> &vec);
    void writeFileInOrder(AVLTreeNode*& node);

    // PROPERTIES
    unsigned int height(AVLTreeNode*& node);

    // AVL PROPERTIES
    void doBalancing(AVLTreeNode*& node);
    unsigned int balanceFactor(AVLTreeNode*& node);

    // AVL ACTIONS
    void simpleLeftRotation(AVLTreeNode*& node);
    void simpleRightRotation(AVLTreeNode*& node);
    void doubleLeftRotation(AVLTreeNode*& node);
    void doubleRightRotation(AVLTreeNode*& node);

    // GET AVL NODE
    AVLTreeNode*& findData(AVLTreeNode*& node,  T& data);
    AVLTreeNode*& lowestData(AVLTreeNode*& node);
    AVLTreeNode*& highestData(AVLTreeNode*& node);    
};

/*
 * PRIVATE METHODS
*/
template<typename T>
void AVLTree<T>::insertData(T& data, AVLTreeNode*& node)
{
    if (node == nullptr)
    {
        node = new AVLTreeNode(data);
        cout << "Inserting item \"" <<  *(node->dataPtr) << "\" in AVL Tree" << endl;
    }
    else if (*(node->dataPtr) == data)
        throw range_error("Data has already been inserted");
    else if (data < *(node->dataPtr))
        insertData(data, node->left);
    else
        insertData(data, node->right);
    doBalancing(node);
}

template<typename T>
void AVLTree<T>::writeFileInOrder(AVLTreeNode*& node)
{
    if (node != nullptr)
    {
        writeFileInOrder(node->left);

        cout << "Writing item \"" << *(node->dataPtr) << "\" in index file" << endl;
        fstream archivoIndices("indices.bin", ios::in | ios::out | ios::binary | ios::app);
        if (!archivoIndices.is_open())
            cout << "Couldn't open index file" << endl;
        archivoIndices.write((char*)node->dataPtr, sizeof(T));
        archivoIndices.close();

        writeFileInOrder(node->right);
    }
}

template<typename T>
void AVLTree<T>::parseInOrder(AVLTreeNode*& node, Vector<T> &vec)
{
    if (node != nullptr)
    {
        parseInOrder(node->left, vec);
        vec.push_back(*(node->dataPtr));
        parseInOrder(node->right, vec);
    }
}

template<typename T>
void AVLTree<T>::parsePreOrder(AVLTreeNode*& node, Vector<T> &vec)
{
    if (node != nullptr)
    {
        vec.push_back(*(node->dataPtr));
        parsePreOrder(node->left, vec);
        parsePreOrder(node->right, vec);
    }
}

template<typename T>
void AVLTree<T>::parsePostOrder(AVLTreeNode*& node, Vector<T> &vec)
{
    if (node != nullptr)
    {
        parsePostOrder(node->left, vec);
        parsePostOrder(node->right, vec);
        vec.push_back(*(node->dataPtr));
    }
}

template<typename T>
unsigned int AVLTree<T>::height(AVLTreeNode*& node)
{
    if (node == nullptr)
        return 0;
    else if (isLeaf(node))
        return 1;
    unsigned int rightHeight = height(node->right);
    unsigned int leftHeight = height(node->left);
    return max(rightHeight, leftHeight) + 1;
}

template<typename T>
void AVLTree<T>::doBalancing(AVLTreeNode*& node)
{
    switch (balanceFactor(node))
    {
        case 2:
            if (balanceFactor(node->right) == 1)
                simpleLeftRotation(node);
            else
                doubleLeftRotation(node);
        break;

        case -2:
            if(balanceFactor(node->left) == -1)
                simpleRightRotation(node);
            else
                doubleRightRotation(node);
        break;
    }
}

template<typename T>
unsigned int AVLTree<T>::balanceFactor(AVLTreeNode*& node)
{
    return height(node->right) - height(node->left);
}

template<typename T>
void AVLTree<T>::simpleLeftRotation(AVLTreeNode*& node)
{
    AVLTreeNode* aux = node->right;
    node->right = aux->left;
    aux->left = node;
    node = aux;
}

template<typename T>
void AVLTree<T>::simpleRightRotation(AVLTreeNode*& node)
{
    AVLTreeNode* aux = node->left;
    node->left = aux->right;
    aux->right = node;
    node = aux;
}

template<typename T>
void AVLTree<T>::doubleLeftRotation(AVLTreeNode*& node)
{
    simpleRightRotation(node->right);
    simpleLeftRotation(node);
}
template<typename T>
void AVLTree<T>::doubleRightRotation(AVLTreeNode*& node)
{
    simpleLeftRotation(node->left);
    simpleRightRotation(node);
}

template<typename T>
typename AVLTree<T>::AVLTreeNode*& AVLTree<T>::findData(AVLTreeNode*& node,  T& data)
{
    if (node == nullptr || *(node->dataPtr) == data)
        return node;
    else
    {
        if (data < *(node->dataPtr))
            findData(node->left, data);
        else
            findData(node->right, data);
    }
}

template<typename T>
typename AVLTree<T>::AVLTreeNode*& AVLTree<T>::lowestData(AVLTreeNode*& node)
{
    if (node == nullptr || node->left == nullptr)
        return node;
    return lowestData(node->left);
}

template<typename T>
typename AVLTree<T>::AVLTreeNode*& AVLTree<T>::highestData(AVLTreeNode*& node)
{
    if (node == nullptr || node->right == nullptr)
        return node;
    return highestData(node->right);
}

template <typename T>
void AVLTree<T>::removeAll(AVLTreeNode*& node)
{
    if (node != nullptr)
    {
        removeAll(node->left);
        removeAll(node->right);
        delete node;
    }
    node = nullptr;
}


/*
 * PUBLIC METHODS
*/
template <typename T>
void AVLTree<T>::removeAll()
{
    removeAll(m_root);
}

template<typename T>
bool AVLTree<T>::isLeaf(AVLTreeNode*& node)
{
    if (node->right == nullptr && node->left == nullptr)
        return true;
    return false;
}

template <typename T>
bool AVLTree<T>::isLeaf()
{
    return isLeaf(m_root);
}

template<typename T>
void AVLTree<T>::insertData( T& data)
{
    insertData(data, m_root);
}

template<typename T>
void AVLTree<T>::writeFileInOrder()
{
    writeFileInOrder(m_root);
}

template<typename T>
void AVLTree<T>::parseInOrder(Vector<T> &vec)
{
    parseInOrder(m_root, vec);
}

template<typename T>
void AVLTree<T>::parsePreOrder(Vector<T> &vec)
{
    parsePreOrder(m_root, vec);
}

template<typename T>
void AVLTree<T>::parsePostOrder(Vector<T> &vec)
{
    parsePostOrder(m_root, vec);
}

template<typename T>
unsigned int AVLTree<T>::height()
{
    return height(m_root);
}

template<typename T>
typename AVLTree<T>::AVLTreeNode*& AVLTree<T>::findData( T& data)
{
    return findData(m_root, data);
}

template<typename T>
typename AVLTree<T>::AVLTreeNode*& AVLTree<T>::lowestData()
{
    return lowestData(m_root);
}

template<typename T>
typename AVLTree<T>::AVLTreeNode*& AVLTree<T>::highestData()
{
    return highestData(m_root);
}

template<typename T>
void AVLTree<T>::removeData(T& data)
{
    AVLTreeNode*& aux = findData(data);
    cout << "Removing item \"" << *(aux->dataPtr) << "\" from AVL Tree" << endl;
    removeNode(aux);
}

template<typename T>
void AVLTree<T>::removeNode(AVLTreeNode*& node)
{
    if (node == nullptr)
        throw range_error("Data doesn't exist");
    else if (isLeaf(node))
    {
        delete node;
        node = nullptr;
    }
    else
    {
        AVLTreeNode*& aux = node->left == nullptr ? lowestData(node->right) : highestData(node->left);
        *(node->dataPtr) = *(aux->dataPtr);
        removeNode(aux);
    }
}

#endif
