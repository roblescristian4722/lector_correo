#include "avl_tree_secundario.h"

AVLTreeSecundario::AVLTreeSecundario()
{ m_root = nullptr; }

AVLTreeSecundario::~AVLTreeSecundario()
{}

AVLTreeSecundario::AVLTreeNode::AVLTreeNode(const string& data)
{
    dataPtr = new IndiceSecundario(data.c_str());
    right = nullptr;
    left = nullptr;
}

AVLTreeSecundario::AVLTreeNode::~AVLTreeNode()
{
    delete dataPtr;
    dataPtr = nullptr;
}

/// PRIVATE METHODS ///
void AVLTreeSecundario::insertData(const string& llave, AVLTreeNode*& node, IndicePrimario*& prim)
{
    if (node == nullptr)
    {
       node = new AVLTreeNode(llave);
       node->dataPtr->getReferencia()->push_back(*prim);
       cout << "Inserting item \"" <<  *(node->dataPtr) << "\" in AVL Tree (Secondary Index)" << endl;
    }
    else if (*(node->dataPtr) == llave)
    {
        LSL<IndicePrimario>*& list = node->dataPtr->getReferencia();
        int pos = busqueda_binaria(atol(prim->getLlave().c_str()), list);
        if (pos == -1)
        {
            list->push_back(*prim);
            shell_sort(list);
            cout << "Inserting item \"" <<  *(node->dataPtr)
                 << "\" in Already existing node (Secondary Index) with "
                 << node->dataPtr->getReferencia()->size() << " items" << endl;
        }
    }
    else if (*(node->dataPtr) > llave)
       insertData(llave, node->left, prim);
    else
       insertData(llave, node->right, prim);

    doBalancing(node);
}

void AVLTreeSecundario::parseInOrder(AVLTreeNode*& node)
{
    if (node != nullptr)
    {
        parseInOrder(node->left);

        LSL<IndicePrimario>* lista = node->dataPtr->getReferencia();
        cout << "Secondary Index Parsing: " << node->dataPtr->getLlave() << " = ";
        for (size_t i = 0; i < lista->size(); i++)
            cout << "llave: " << (*lista)[i].getLlave() << " | ref: " << (*lista)[i].getReferencia() << ", ";
        cout << endl;
        lista = nullptr;

        parseInOrder(node->right);
    }
}

int AVLTreeSecundario::height(AVLTreeNode*& node)
{
   if (node == nullptr)
       return 0;
   else if (isLeaf(node))
       return 1;
   int rightHeight = height(node->right);
   int leftHeight = height(node->left);
   return max(rightHeight, leftHeight) + 1;
}

void AVLTreeSecundario::doBalancing(AVLTreeNode*& node)
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

int AVLTreeSecundario::balanceFactor(AVLTreeNode*& node)
{
   return height(node->right) - height(node->left);
}

void AVLTreeSecundario::simpleLeftRotation(AVLTreeNode*& node)
{
   AVLTreeNode* aux = node->right;
   node->right = aux->left;
   aux->left = node;
   node = aux;
}

void AVLTreeSecundario::simpleRightRotation(AVLTreeNode*& node)
{
   AVLTreeNode* aux = node->left;
   node->left = aux->right;
   aux->right = node;
   node = aux;
}

void AVLTreeSecundario::doubleLeftRotation(AVLTreeNode*& node)
{
   simpleRightRotation(node->right);
   simpleLeftRotation(node);
}

void AVLTreeSecundario::doubleRightRotation(AVLTreeNode*& node)
{
   simpleLeftRotation(node->left);
   simpleRightRotation(node);
}

AVLTreeSecundario::AVLTreeNode*& AVLTreeSecundario::findData(AVLTreeNode*& node, const string& data)
{
   if (node == nullptr || *(node->dataPtr) == data)
       return node;
   else
   {
       if (*(node->dataPtr) > data)
           return findData(node->left, data);
       else
           return findData(node->right, data);
   }
}

AVLTreeSecundario::AVLTreeNode*& AVLTreeSecundario::lowestData(AVLTreeNode*& node)
{
   if (node == nullptr || node->left == nullptr)
       return node;
   return lowestData(node->left);
}

typename AVLTreeSecundario::AVLTreeNode*& AVLTreeSecundario::highestData(AVLTreeNode*& node)
{
   if (node == nullptr || node->right == nullptr)
       return node;
   return highestData(node->right);
}

void AVLTreeSecundario::removeAll(AVLTreeNode*& node)
{
    if (node != nullptr)
    {
        removeAll(node->left);
        removeAll(node->right);
        delete node;
    }
    node = nullptr;
}

void AVLTreeSecundario::removePrimary(long id, AVLTreeSecundario::AVLTreeNode *&node)
{
    if (node == nullptr)
        throw range_error("Node doesn't exist");
    else
    {
        cout << id << endl;
        LSL<IndicePrimario>*& list = node->dataPtr->getReferencia();
        int pos = busqueda_binaria(id, list);
        cout << "Removing item \"" << (*list)[size_t(pos)].getLlave()
             << "\" with position " << pos << "in list" << endl;
        list->erase(size_t(pos));
        if (!list->size())
            removeNode(node);
    }
}


/// PUBLIC METHODS ///
void AVLTreeSecundario::removeAll()
{ removeAll(m_root); }

bool AVLTreeSecundario::isLeaf(AVLTreeNode*& node)
{
   if (node->right == nullptr && node->left == nullptr)
       return true;
   return false;
}

bool AVLTreeSecundario::isLeaf()
{ return isLeaf(m_root); }

void AVLTreeSecundario::insertData(const string& llave, IndicePrimario*& prim)
{ insertData(llave, m_root, prim); }

void AVLTreeSecundario::parseInOrder()
{ parseInOrder(m_root); }

int AVLTreeSecundario::height()
{ return height(m_root); }

AVLTreeSecundario::AVLTreeNode*& AVLTreeSecundario::findData(const string& data)
{ return findData(m_root, data); }

AVLTreeSecundario::AVLTreeNode*& AVLTreeSecundario::lowestData()
{ return lowestData(m_root); }

AVLTreeSecundario::AVLTreeNode*& AVLTreeSecundario::highestData()
{ return highestData(m_root); }

void AVLTreeSecundario::removeData(const string& data)
{
   AVLTreeNode*& aux = findData(data);
   cout << "Removing item \"" << *(aux->dataPtr) << "\" from AVL Tree" << endl;
   removeNode(aux);
}

void AVLTreeSecundario::removeNode(AVLTreeNode*& node)
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
       AVLTreeNode*& aux = (node->left == nullptr) ? lowestData(node->right) : highestData(node->left);
       *(node->dataPtr) = *(aux->dataPtr);
       removeNode(aux);
   }
}

void AVLTreeSecundario::removePrimary(const string data, long id)
{
    AVLTreeNode *& node = findData(data);
    removePrimary(id, node);
}

/// EXTRA ///
int AVLTreeSecundario::busqueda_binaria(long id, LSL<IndicePrimario>*& lista)
{
    int l = 0;
    int r = int(lista->size() - 1);
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (id == atol((*lista)[size_t(m)].getLlave().c_str()))
            return m;
        else if (id < atol((*lista)[size_t(m)].getLlave().c_str()))
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}

void AVLTreeSecundario::shell_sort(LSL<IndicePrimario>*& list)
{
    size_t n = list->size();
    size_t brecha = n / 2;
    size_t j;
    IndicePrimario tmp;
    while (brecha > 0)
    {
        for (size_t i = brecha; i < n; ++i)
        {
            tmp = (*list)[i];
            j = i;
            while (j >= brecha && atol((*list)[j - brecha].getLlave().c_str()) > atol(tmp.getLlave().c_str()))
            {
                (*list)[j] = (*list)[j - brecha];
                j -= brecha;
            }
            (*list)[j] = tmp;
        }
        brecha /= 2;
    }
}

