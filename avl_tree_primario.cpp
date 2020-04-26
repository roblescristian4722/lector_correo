#include "avl_tree_primario.h"

AVLTreePrimario::AVLTreePrimario()
{
    m_root = nullptr;
    m_size = 0;
}

AVLTreePrimario::~AVLTreePrimario()
{ m_LRU.clear(); }

AVLTreePrimario::AVLTreeNode::AVLTreeNode(IndicePrimario &data)
{
    dataPtr = new IndicePrimario(data);
    right = nullptr;
    left = nullptr;
    time = chrono::high_resolution_clock::now().time_since_epoch().count();
}

AVLTreePrimario::AVLTreeNode::~AVLTreeNode()
{
    delete dataPtr;
    dataPtr = nullptr;
}

/// PRIVATE METHODS ///
void AVLTreePrimario::insertData(IndicePrimario& data, AVLTreeNode*& node)
{
    if (node == nullptr){
        node = new AVLTreeNode(data);
        cout << "Inserting item \"" << *(node->dataPtr) << "\" in AVL Tree (Primary Index)" << endl;    
        ++m_size;
        m_LRU.push_back(node->dataPtr);
    }
    else if (*(node->dataPtr) == data)
            throw range_error("Data has already been inserted");
    else if (data < *(node->dataPtr))
        insertData(data, node->left);
    else
        insertData(data, node->right);
    doBalancing(node);
}

void AVLTreePrimario::writeFileInOrder(AVLTreeNode*& node)
{
    if (node != nullptr){
       writeFileInOrder(node->left);

       long pos;
       cout << "Writing item \"" << *(node->dataPtr) << "\" " << node->dataPtr->getReferencia() << " in index file" << endl;
       fstream archivoIndices("indices.bin", ios::in | ios::out | ios::binary);
       if (!archivoIndices.is_open())
           cout << "Couldn't open index file" << endl;
       pos = atol(node->dataPtr->getLlave().c_str()) * long(sizeof(IndicePrimario));
       archivoIndices.seekp(pos);
       archivoIndices.write((char*)node->dataPtr, sizeof(IndicePrimario));
       archivoIndices.close();

       writeFileInOrder(node->right);
    }
}

void AVLTreePrimario::parseInOrder(AVLTreeNode*& node, Vector<IndicePrimario> &vec)
{
   if (node != nullptr){
       parseInOrder(node->left, vec);
       vec.push_back(*(node->dataPtr));
       parseInOrder(node->right, vec);
   }
}

int AVLTreePrimario::height(AVLTreeNode*& node)
{
   if (node == nullptr)
       return 0;
   else if (isLeaf(node))
       return 1;
   int rightHeight = height(node->right);
   int leftHeight = height(node->left);
   return max(rightHeight, leftHeight) + 1;
}

void AVLTreePrimario::doBalancing(AVLTreeNode*& node)
{
   switch (balanceFactor(node)){
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

int AVLTreePrimario::balanceFactor(AVLTreeNode*& node)
{ return height(node->right) - height(node->left); }

void AVLTreePrimario::simpleLeftRotation(AVLTreeNode*& node)
{
   AVLTreeNode* aux = node->right;
   node->right = aux->left;
   aux->left = node;
   node = aux;
}

void AVLTreePrimario::simpleRightRotation(AVLTreeNode*& node)
{
   AVLTreeNode* aux = node->left;
   node->left = aux->right;
   aux->right = node;
   node = aux;
}

void AVLTreePrimario::doubleLeftRotation(AVLTreeNode*& node)
{
   simpleRightRotation(node->right);
   simpleLeftRotation(node);
}

void AVLTreePrimario::doubleRightRotation(AVLTreeNode*& node)
{
   simpleLeftRotation(node->left);
   simpleRightRotation(node);
}

AVLTreePrimario::AVLTreeNode*& AVLTreePrimario::findData(AVLTreeNode*& node,  IndicePrimario& data)
{
   if (node == nullptr || *(node->dataPtr) == data)
       return node;
   else{
       if (data < *(node->dataPtr))
           return findData(node->left, data);
       else
           return findData(node->right, data);
   }
}

AVLTreePrimario::AVLTreeNode*& AVLTreePrimario::lowestData(AVLTreeNode*& node)
{
   if (node == nullptr || node->left == nullptr)
       return node;
   return lowestData(node->left);
}

typename AVLTreePrimario::AVLTreeNode*& AVLTreePrimario::highestData(AVLTreeNode*& node)
{
   if (node == nullptr || node->right == nullptr)
       return node;
   return highestData(node->right);
}

void AVLTreePrimario::removeAll(AVLTreeNode*& node)
{
   if (node != nullptr){
       removeAll(node->left);
       removeAll(node->right);
       delete node;
   }
   node = nullptr;
}


/// PUBLIC METHODS ///
void AVLTreePrimario::removeAll()
{
    removeAll(m_root);
    m_LRU.clear();
    m_size = 0;
}

bool AVLTreePrimario::isLeaf(AVLTreeNode*& node)
{
   if (node->right == nullptr && node->left == nullptr)
       return true;
   return false;
}

bool AVLTreePrimario::isLeaf()
{ return isLeaf(m_root); }

void AVLTreePrimario::insertData(IndicePrimario& data)
{ insertData(data, this->m_root); }

void AVLTreePrimario::writeFileInOrder()
{
    fstream archivoIndices("indices.bin", ios::out | ios::binary);
    IndicePrimario indiceTmp;
    // Se activa la bandera para indicar que los datos se guardaron
    // correctamente
    indiceTmp.setReferencia(1);
    archivoIndices.write((char*)&indiceTmp, sizeof(IndicePrimario));
    archivoIndices.close();

    writeFileInOrder(m_root);
}

void AVLTreePrimario::parseInOrder(Vector<IndicePrimario> &vec)
{ parseInOrder(m_root, vec); }

int AVLTreePrimario::height()
{ return height(m_root); }

AVLTreePrimario::AVLTreeNode*& AVLTreePrimario::operator[](IndicePrimario& data)
{ return findData(m_root, data); }

AVLTreePrimario::AVLTreeNode*& AVLTreePrimario::lowestData()
{ return lowestData(m_root); }

AVLTreePrimario::AVLTreeNode*& AVLTreePrimario::highestData()
{ return highestData(m_root); }

long AVLTreePrimario::getSize() const
{ return m_size; }

void AVLTreePrimario::setSize(const long &size)
{ m_size = size; }

Vector<IndicePrimario *> AVLTreePrimario::getLRU() const
{ return m_LRU; }

void AVLTreePrimario::setLRU(const Vector<IndicePrimario *> &LRU)
{ m_LRU = LRU; }

void AVLTreePrimario::removeData(IndicePrimario& data, bool removeFromList)
{
    AVLTreeNode*& aux = (*this)[data];
    removeNode(aux, removeFromList);
}

void AVLTreePrimario::removeNode(AVLTreeNode*& node, bool removeFromList)
{
    if (node == nullptr)
         throw range_error("Data doesn't exist");
    else if (isLeaf(node)){
        cout << "Removing item \"" << (*node->dataPtr) << "\" from AVL Tree" << endl;
        if (removeFromList){
            int res_aux = binary_search(*node->dataPtr);
            m_LRU.erase(size_t(res_aux));
            shell_sort();
        }
        delete node;
        node = nullptr;
        --m_size;
    }
    else{
        AVLTreeNode*& aux = node->left == nullptr ? lowestData(node->right) : highestData(node->left);
        *(node->dataPtr) = *(aux->dataPtr);
        node->time = aux->time;
        removeNode(aux, removeFromList);
    }
}

void AVLTreePrimario::removeLRU()
{
    shell_sort();
    while (m_LRU.size() >= PAG_MAX_SIZE){
        AVLTreeNode* indice = findData(m_root, *(m_LRU[0]));
        removeNode(indice, true);
    }
    shell_sort();
}

/// EXTRA ///
void AVLTreePrimario::shell_sort()
{
    size_t n = m_LRU.size();
    size_t brecha = n / 2;
    size_t j;
    IndicePrimario* tmp;
    while (brecha > 0){
        for (size_t i = brecha; i < n; ++i){
            tmp = m_LRU[i];
            j = i;
            AVLTreeNode*& first = findData(m_root, *m_LRU[j - brecha]);
            AVLTreeNode*& second = findData(m_root, *tmp);
            while (j >= brecha && first->time > second->time){
                m_LRU[j] = m_LRU[j - brecha];
                j -= brecha;
            }
            m_LRU[j] = tmp;
        }
        brecha /= 2;
    }
}


int AVLTreePrimario::binary_search(IndicePrimario& data)
{
    int l = 0;
    int r = int(m_LRU.size() - 1);
    while (l <= r)
    {
        int m = (l + r) / 2;
        AVLTreeNode*& dataNode = findData(m_root, data);
        AVLTreeNode*& cmpNode = findData(m_root, *m_LRU[size_t(m)]);
        if (dataNode->time == cmpNode->time)
            return m;
        else if (dataNode->time < cmpNode->time)
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}
