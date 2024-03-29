#ifndef AVL_TREE_PRIMARIO
#define AVL_TREE_PRIMARIO

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <chrono>
#include "correo.h"
#include "vector.h"
#include "indices.h"
#include "avl_tree_secundario.h"

#define PAG_MAX_SIZE 10
using namespace std;

class AVLTreePrimario
{
public:
    struct AVLTreeNode
    {
        IndicePrimario* dataPtr;
        AVLTreeNode* right;
        AVLTreeNode* left;

        long time;
        AVLTreeNode(IndicePrimario& data);
        ~AVLTreeNode();
    };

    AVLTreePrimario();
    ~AVLTreePrimario();

    // MODIFY DATA
    void insertData(IndicePrimario& data);
    void removeData(IndicePrimario& data, bool removeFromList = false);
    void removeNode(AVLTreeNode*& node, bool removeFromList = false);
    void removeLRU();
    void removeAll();

    // PARSE
    void writeFileInOrder();
    void parseInOrder(Vector<IndicePrimario> &vec);

    // PROPERTIES
    bool isLeaf();
    bool isLeaf(AVLTreeNode*& node);
    int height();

    // GET AVL DATA
    AVLTreeNode*& operator [](IndicePrimario& data);
    AVLTreeNode*& lowestData();
    AVLTreeNode*& highestData();

    // EXTRA
    void shell_sort();

    long getSize() const;
    void setSize(const long &size);

    Vector<IndicePrimario *> getLRU() const;
    void setLRU(const Vector<IndicePrimario *> &LRU);

private:
    AVLTreeNode* m_root;
    Vector<IndicePrimario*> m_LRU;
    long m_size;

    // MODIFY DATA
    void insertData(IndicePrimario& data, AVLTreeNode*& node);
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

    // EXTRA
    int binary_search(IndicePrimario& data);
};

#endif
