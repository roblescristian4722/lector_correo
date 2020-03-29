#ifndef AVL_TREE_SECUNDARIO_H
#define AVL_TREE_SECUNDARIO_H

#include <iostream>
#include <stdexcept>
#include <fstream>
#include "vector.h"
#include "indices.h"
using namespace std;

class AVLTreeSecundario
{
public:
    struct AVLTreeNode
    {
        IndiceSecundario* dataPtr;
        AVLTreeNode* right;
        AVLTreeNode* left;

        AVLTreeNode(const string & data);
        ~AVLTreeNode();
    };

    AVLTreeSecundario();
    ~AVLTreeSecundario();

    // MODIFY DATA
    void insertData(const string& llave, IndicePrimario*& prim);
    void removeData(const string& data);
    void removeNode(AVLTreeNode*& node);
    void removePrimary(const string data, long id);
    void removeAll();

    // PARSE
    void parseInOrder();

    // PROPERTIES
    bool isLeaf();
    bool isLeaf(AVLTreeNode*& node);
    int height();

    // GET AVL DATA
    AVLTreeNode*& findData(const string& data);
    AVLTreeNode*& lowestData();
    AVLTreeNode*& highestData();

private:
    AVLTreeNode* m_root;

    // MODIFY DATA
    void insertData(const string& llave, AVLTreeNode*& node, IndicePrimario*& prim);
    void removeAll(AVLTreeNode*& node);
    void removePrimary(long id, AVLTreeNode*& node);

    // PARSE
    void parseInOrder(AVLTreeNode*& node);

    // PROPERTIES
    int height(AVLTreeNode*& node);

    // AVL PROPERTIES
    void doBalancing(AVLTreeNode*& node);
    int balanceFactor(AVLTreeNode*& node);

    // AVL ACTIONS
    void simpleLeftRotation(AVLTreeNode*& node);
    void simpleRightRotation(AVLTreeNode*& node);
    void doubleLeftRotation(AVLTreeNode*& node);
    void doubleRightRotation(AVLTreeNode*& node);

    // GET AVL NODE
    AVLTreeNode*& findData(AVLTreeNode*& node,  const string& data);
    AVLTreeNode*& lowestData(AVLTreeNode*& node);
    AVLTreeNode*& highestData(AVLTreeNode*& node);

    int busqueda_binaria(long dato, LSL<IndicePrimario>*& list);
};

#endif
