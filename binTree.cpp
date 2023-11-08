#include "main.h"

enum TraversalType { DF_NLR, DF_NRL, DF_RNL, DF_RLN, DF_LNR, DF_LRN, BF };

template<class T>
class BinTree {
public:
    struct Node {
        T   data;
        Node* pLeft;
        Node* pRight;
        Node(const T & val, Node *pL = nullptr, Node *pR = nullptr): data(val), pLeft(pL), pRight(pR) {}
        Node(T && val, Node *pL = nullptr, Node *pR = nullptr): data(std::move(val)), pLeft(pL), pRight(pR) {}
    };
    Node *pRoot;
public:
    BinTree(Node *pRoot = nullptr): pRoot(pRoot) {}
    ~BinTree() { clear(); }
    void    clear() {
        clear(pRoot);
        pRoot = nullptr;
    }

    void tranverse(std::function<void (T&)> op, TraversalType type = DF_NLR) {
        switch (type) {
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

protected:
    void    clear(Node *pRoot) {
        if (pRoot) {
            clear(pRoot->pLeft);
            clear(pRoot->pRight);
            delete pRoot;
        }
    }

    void    tranverseNLR(Node *pRoot, std::function<void (T&)> op) {
        if (pRoot) {
            op(pRoot->data);
            tranverseNLR(pRoot->pLeft, op);
            tranverseNLR(pRoot->pRight, op);
        }
    }

    void    tranverseNRL(Node *pRoot, std::function<void (T&)> op) {
        if (pRoot) {
            op(pRoot->data);
            tranverseNRL(pRoot->pRight, op);
            tranverseNRL(pRoot->pLeft, op);
        }
    }

    void    tranverseRNL(Node *pRoot, std::function<void (T&)> op) {
        if (pRoot) {
            tranverseRNL(pRoot->pRight, op);
            op(pRoot->data);
            tranverseRNL(pRoot->pLeft, op);
        }
    }

    void    tranverseRLN(Node *pRoot, std::function<void (T&)> op) {
        if (pRoot) {
            tranverseRLN(pRoot->pRight, op);
            tranverseRLN(pRoot->pLeft, op);
            op(pRoot->data);
        }
    }

    void    tranverseLNR(Node *pRoot, std::function<void (T&)> op) {
        if (pRoot) {
            tranverseLNR(pRoot->pLeft, op);
            op(pRoot->data);
            tranverseLNR(pRoot->pRight, op);
        }
    }

    void    tranverseLRN(Node *pRoot, std::function<void (T&)> op) {
        if (pRoot) {
            tranverseLRN(pRoot->pLeft, op);
            tranverseLRN(pRoot->pRight, op);
            op(pRoot->data);
        }
    }

    void tranverseBF(Node *pRoot, std::function<void (T&)> op) {
        queue<Node *> store;
        if (pRoot) store.push(pRoot);
        while (!store.empty()) {
            Node *p = store.front();
            store.pop();
            op(pRoot->data);

            if (p->pLeft) store.push(p->pLeft);
            if (p->pRight) store.push(p->pRight);
        }
    }
};
