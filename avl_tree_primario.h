#ifndef AVL_TREE_PRIMARIO
#define AVL_TREE_PRIMARIO

#include <iostream>
#include <stdexcept>
#include <fstream>
#include "correo.h"
#include "vector.h"
#include "indices.h"
#include "avl_tree_secundario.h"
using namespace std;

class AVLTreePrimario
{
public:
    struct AVLTreeNode
    {
        IndicePrimario* dataPtr;
        AVLTreeNode* right;
        AVLTreeNode* left;

        AVLTreeNode(IndicePrimario& data);
        ~AVLTreeNode();
    };

    AVLTreePrimario();
    ~AVLTreePrimario();

    // MODIFY DATA
    void insertData(IndicePrimario& data, AVLTreeSecundario*& rem, AVLTreeSecundario*& des, bool mod = false);
    void removeData(IndicePrimario& data);
    void removeNode(AVLTreeNode*& node);
    void removeAll();

    // PARSE
    void writeFileInOrder();
    void parseInOrder(Vector<IndicePrimario> &vec);

    // PROPERTIES
    bool isLeaf();
    bool isLeaf(AVLTreeNode*& node);
    int height();

    // GET AVL DATA
    AVLTreeNode*& findData(IndicePrimario& data);
    AVLTreeNode*& lowestData();
    AVLTreeNode*& highestData();

private:
    AVLTreeNode* m_root;

    // MODIFY DATA
    void insertData(IndicePrimario& data, AVLTreeNode*& node, AVLTreeSecundario*& rem, AVLTreeSecundario*& des, bool mod = false);
    void removeAll(AVLTreeNode*& node);

    // PARSE
    void parseInOrder(AVLTreeNode*& node, Vector<IndicePrimario> &vec);
    void writeFileInOrder(AVLTreeNode*& node);

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
    AVLTreeNode*& findData(AVLTreeNode*& node,  IndicePrimario& data);
    AVLTreeNode*& lowestData(AVLTreeNode*& node);
    AVLTreeNode*& highestData(AVLTreeNode*& node);
};

#endif
