// Binary Search Tree
#include "main.h"

enum TraversalType
{
    DF_NLR,
    DF_NRL,
    DF_RNL,
    DF_RLN,
    DF_LNR,
    DF_LRN,
    BF
};

template <class T>
class BinarySearchTree
{
public:
    struct Node
    {
        T data;
        Node *pLeft;
        Node *pRight;
        Node(const T &val, Node *pL = nullptr, Node *pR = nullptr) : data(val), pLeft(pL), pRight(pR) {}
        Node(T &&val, Node *pL = nullptr, Node *pR = nullptr) : data(std::move(val)), pLeft(pL), pRight(pR) {}
    };
    Node *pRoot;

public:
    BinarySearchTree(Node *pRoot = nullptr) : pRoot(pRoot) {}
    ~BinarySearchTree() { clear(); }
    void clear()
    {
        clear(pRoot);
        pRoot = nullptr;
    }

    void tranverse(std::function<void(T &)> op, TraversalType type = DF_NLR)
    {
        switch (type)
        {
        case DF_NLR:
            tranverseNLR(pRoot, op);
            break;
        case DF_NRL:
            tranverseNRL(pRoot, op);
            break;
        case DF_RNL:
            tranverseRNL(pRoot, op);
            break;
        case DF_RLN:
            tranverseRLN(pRoot, op);
            break;
        case DF_LNR:
            tranverseLNR(pRoot, op);
            break;
        case DF_LRN:
            tranverseLRN(pRoot, op);
            break;
        case BF:
            tranverseBF(pRoot, op);
            break;
        default:
            break;
        }
    }

    T *find(const T &key)
    {
        // return find(this->pRoot, key);
        Node *p = pRoot;
        while (p != nullptr)
        {
            if (p->data)
                return &p->data;
            if (p->data > key)
                p = p->pLeft;
            else
                p = p->pRight;
        }
        return nullptr;
    }

    void insert(const T &key)
    {
        // insert(this->pRoot, key);
        Node **pNode = &pRoot;
        while (*pNode != nullptr)
        {
            if ((*pNode)->data > key)
                pNode = &(*pNode)->pLeft;
            else
                pNode = &(*pNode)->pRight;
        }
        *pNode = new Node(key);
    }

    void remove(const T &key)
    {
        remove(this->pRoot, key);
    }

protected:
    void clear(Node *pRoot)
    {
        if (pRoot)
        {
            clear(pRoot->pLeft);
            clear(pRoot->pRight);
            delete pRoot;
        }
    }

    void tranverseNLR(Node *pRoot, std::function<void(T &)> op)
    {
        if (pRoot)
        {
            op(pRoot->data);
            tranverseNLR(pRoot->pLeft, op);
            tranverseNLR(pRoot->pRight, op);
        }
    }

    void tranverseNRL(Node *pRoot, std::function<void(T &)> op)
    {
        if (pRoot)
        {
            op(pRoot->data);
            tranverseNRL(pRoot->pRight, op);
            tranverseNRL(pRoot->pLeft, op);
        }
    }

    void tranverseRNL(Node *pRoot, std::function<void(T &)> op)
    {
        if (pRoot)
        {
            tranverseRNL(pRoot->pRight, op);
            op(pRoot->data);
            tranverseRNL(pRoot->pLeft, op);
        }
    }

    void tranverseRLN(Node *pRoot, std::function<void(T &)> op)
    {
        if (pRoot)
        {
            tranverseRLN(pRoot->pRight, op);
            tranverseRLN(pRoot->pLeft, op);
            op(pRoot->data);
        }
    }

    void tranverseLNR(Node *pRoot, std::function<void(T &)> op)
    {
        if (pRoot)
        {
            tranverseLNR(pRoot->pLeft, op);
            op(pRoot->data);
            tranverseLNR(pRoot->pRight, op);
        }
    }

    void tranverseLRN(Node *pRoot, std::function<void(T &)> op)
    {
        if (pRoot)
        {
            tranverseLRN(pRoot->pLeft, op);
            tranverseLRN(pRoot->pRight, op);
            op(pRoot->data);
        }
    }

    void tranverseBF(Node *pRoot, std::function<void(T &)> op)
    {
        queue<Node *> store;
        if (pRoot)
            store.push(pRoot);
        while (!store.empty())
        {
            Node *p = store.front();
            store.pop();
            op(pRoot->data);

            if (p->pLeft)
                store.push(p->pLeft);
            if (p->pRight)
                store.push(p->pRight);
        }
    }

    T *find(Node *pRoot, const T &key)
    {
        if (pRoot)
        {
            if (pRoot->data == key)
                return &pRoot->data;
            if (pRoot->data > key)
                return find(pRoot->pLeft, key);
            else
                return find(pRoot->pRight, key);
        }
        return nullptr;
    }

    void insert(Node *&pRoot, const T &key)
    {
        if (pRoot)
        {
            if (pRoot->data > key)
                insert(pRoot->pLeft, key);
            else
                insert(pRoot->pRight, key);
            return;
        }
        pRoot = new Node(key);
    }

    void remove(Node *&pRoot, const T &key)
    {
        if (!pRoot)
            return;

        Node *temp;
        if (pRoot->data == key)
        {
            if (pRoot->pLeft && pRoot->pRight)
            {
                temp = pRoot->pRight;
                while (temp->pLeft != nullptr)
                    temp = temp->pLeft;
                pRoot->data = temp->data;
                remove(pRoot->pRight, pRoot->data);
            }
            else if (pRoot->pLeft)
            {
                temp = pRoot;
                pRoot = pRoot->pLeft;
                delete temp;
            }
            else if (pRoot->pRight)
            {
                temp = pRoot;
                pRoot = pRoot->pRight;
                delete temp;
            }
            else
            {
                delete pRoot;
                pRoot = nullptr;
            }
        }
        else if (pRoot->data > key)
            return remove(pRoot->pLeft, key);
        else
            return remove(pRoot->pRight, key);
    }
};
