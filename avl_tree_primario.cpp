#include "avl_tree_primario.h"

AVLTreePrimario::AVLTreePrimario()
{
    m_root = nullptr;
    m_size = 0;
}

AVLTreePrimario::~AVLTreePrimario()
{ m_leastVisited.clear(); }

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
void AVLTreePrimario::insertData(IndicePrimario& data, AVLTreeNode*& node, AVLTreeSecundario*& rem, AVLTreeSecundario*& des, bool mod)
{
    if (node == nullptr){
        node = new AVLTreeNode(data);
        cout << "Inserting item \"" << *(node->dataPtr) << "\" in AVL Tree (Primary Index)" << endl;

        Correo correoTmp;
        fstream archivo("datos.bin", ios::in | ios::binary);

        archivo.seekg(data.getReferencia());
        archivo.read((char*)&correoTmp, sizeof(Correo));
        archivo.close();
        ++m_size;
        m_leastVisited.push_back(node->dataPtr);
        rem->insertData(correoTmp.getRem(), node->dataPtr);
        des->insertData(correoTmp.getDestinatario(), node->dataPtr);
    }
    else if (*(node->dataPtr) == data)
        if (!mod)
            throw range_error("Data has already been inserted");
        else{
            Correo correoTmp;
            fstream archivo("datos.bin", ios::in | ios::binary);

            archivo.seekg(data.getReferencia());
            archivo.read((char*)&correoTmp, sizeof(Correo));
            archivo.close();

            rem->insertData(correoTmp.getRem(), node->dataPtr);
            des->insertData(correoTmp.getDestinatario(), node->dataPtr);
        }
    else if (data < *(node->dataPtr))
        insertData(data, node->left, rem, des, mod);
    else
        insertData(data, node->right, rem, des, mod);
    doBalancing(node);
}

void AVLTreePrimario::writeFileInOrder(AVLTreeNode*& node)
{
    if (node != nullptr){
       writeFileInOrder(node->left);

       long pos;
       cout << "Writing item \"" << *(node->dataPtr) << "\" in index file" << endl;
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
    m_leastVisited.clear();
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

void AVLTreePrimario::insertData(IndicePrimario& data, AVLTreeSecundario* &rem, AVLTreeSecundario*&des, bool mod)
{ insertData(data, this->m_root, rem, des, mod); }

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

AVLTreePrimario::AVLTreeNode*& AVLTreePrimario::findData(IndicePrimario& data)
{ return findData(m_root, data); }

AVLTreePrimario::AVLTreeNode*& AVLTreePrimario::lowestData()
{ return lowestData(m_root); }

AVLTreePrimario::AVLTreeNode*& AVLTreePrimario::highestData()
{ return highestData(m_root); }

long AVLTreePrimario::getSize() const
{ return m_size; }

void AVLTreePrimario::setSize(const long &size)
{ m_size = size; }

Vector<IndicePrimario *> AVLTreePrimario::getLeastVisited() const
{ return m_leastVisited; }

void AVLTreePrimario::setLeastVisited(const Vector<IndicePrimario *> &leastVisited)
{ m_leastVisited = leastVisited; }

void AVLTreePrimario::removeData(IndicePrimario& data)
{
    AVLTreeNode*& aux = findData(data);
    removeNode(aux);
}

void AVLTreePrimario::removeNode(AVLTreeNode*& node)
{
    if (node == nullptr)
         throw range_error("Data doesn't exist");
    else if (isLeaf(node))
    {
        cout << "Removing item \"" << (*node->dataPtr) << "\" from AVL Tree" << endl;
        int res = binary_search(*node->dataPtr);
        if (res != -1)
           m_leastVisited.erase(size_t(res));

        delete node;
        node = nullptr;
        --m_size;
    }
    else
    {
        AVLTreeNode*& aux = node->left == nullptr ? lowestData(node->right) : highestData(node->left);
        *(node->dataPtr) = *(aux->dataPtr);
        removeNode(aux);
    }
}

void AVLTreePrimario::removeLeastVisited()
{
    for (size_t i = 0; m_leastVisited.size() >= PAG_MAX_SIZE; ++i)
        removeNode(findData(*(m_leastVisited[0])));
}

/// EXTRA ///
void AVLTreePrimario::shell_sort()
{
    size_t n = m_leastVisited.size();
    size_t brecha = n / 2;
    size_t j;
    IndicePrimario* tmp;
    while (brecha > 0){
        for (size_t i = brecha; i < n; ++i){
            tmp = m_leastVisited[i];
            j = i;
            while (j >= brecha && findData(*m_leastVisited[j - brecha])->time > findData(*tmp)->time){
                m_leastVisited[j] = m_leastVisited[j - brecha];
                j -= brecha;
            }
            m_leastVisited[j] = tmp;
        }
        brecha /= 2;
    }
}

int AVLTreePrimario::binary_search(IndicePrimario& data)
{
    int l = 0;
    int r = int(m_leastVisited.size() - 1);
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (data == *m_leastVisited[size_t(m)])
            return m;
        else if (data < *m_leastVisited[size_t(m)])
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}
