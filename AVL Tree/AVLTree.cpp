#include "main.h"

template<class T>
class AVLTree {
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
    AVLTree(): pRoot(nullptr) {};
    ~AVLTree() { clear(); }
    void    clear() {
        clear(pRoot);
    }

    int     getHeight()
    {
        return this->getHeightRec(this->root);
    }

    void    printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    void rotateLeft() {
        
    }
protected:
    void clear(Node *root) {
        if (root == nullptr) return;
        clear(root->pLeft);
        clear(root->pRight);
        delete root;
        root = nullptr;
    }

    int getHeightRec(Node *root) {
        if (root == nullptr) return 0;
        int leftH = getHeightRec(root->pLeft);
        int rightH = getHeightRec(root->pRight);
        return leftH > rightH ? leftH + 1 : rightH + 1;
    }
};