#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

enum Color
{
    RED,
    BLACK
};
struct node
{
    int key;
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;
    Color color = BLACK;
};

typedef node* NodePtr;

class RBT
{
public:
    NodePtr root;
    NodePtr leafNode;

    NodePtr IsKey(int item)
    {
        NodePtr t = root;
        NodePtr parent = NULL;

        while (t != NULL && t->key != item)
        {
            parent = t;
            t = (item < parent->key) ? parent->left : parent->right;
        }
        return t;
    }

    void Insertion(int item)
    {
        NodePtr x = this->root, y = nullptr;
        NodePtr z = new node();
        z->key = item;
        z->color = RED;
        z->parent = nullptr;
        z->left = leafNode;
        z->right = leafNode;

        while (x != leafNode)
        {
            y = x;
            if (x->key < item)
                x = x->right;
            else
                x = x->left;
        }

        z->parent = y;

        if (y == nullptr)
            root = z;
        else if (z->key > y->key)
            y->right = z;
        else
            y->left = z;

        if (z->parent == nullptr)
        {
            z->color = BLACK;
            return;
        }
        if (z->parent->parent == nullptr)
        {
            return;
        }
        InsertFixUp(z);

        return;
    }

    void InsertFixUp(NodePtr z)
    {
        while (z != root && z->parent->color == RED)
        {
            NodePtr grandparent = z->parent->parent;
            NodePtr uncle = (z->parent == grandparent->left) ? grandparent->right : grandparent->left;
            bool side = (z->parent == grandparent->left) ? true : false;

            /*case 1*/
            if (uncle && uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            }
            else
            {
                if (z == (side ? z->parent->right : z->parent->left))
                {
                    z = z->parent;
                    side ? leftRotate(z) : rightRotate(z);
                }
                z->parent->color = BLACK;
                grandparent->color = RED;
                side ? rightRotate(grandparent) : leftRotate(grandparent);
            }
        }
        root->color = BLACK;
    }

    bool Deletion(int item)
    {
        NodePtr z = IsKey(item);
        if (!z)
            return false;
        else
        {
            NodePtr x, y;
            Color OriginalColor = z->color;

            if (z->left == leafNode)
            {
                x = z->right;
                Transplant(z, z->right);
            }
            else if (z->right == leafNode)
            {
                x = z->left;
                Transplant(z, z->left);
            }
            else
            {
                y = tree_minimum(z->right);
                OriginalColor = y->color;
                x = y->right;

                if (y->parent == z)
                {
                    x->parent = y;
                }
                else
                {
                    Transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                Transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            delete z;
            if (OriginalColor == BLACK)
            {
                DelteFixUp(x);
            }
        }
        return true;
    }

    void DelteFixUp(NodePtr x)
    {
        NodePtr s;
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == BLACK)
                    {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->left->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == BLACK)
                    {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
        root->color = BLACK;
    }
    void Transplant(NodePtr u, NodePtr v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent;
    }
    void leftRotate(NodePtr x)
    {
        NodePtr y;

        y = x->right;
        x->right = y->left;
        if (y->left != leafNode)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;

        if (!x->parent)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        x->parent = y;
        y->left = x;
    }
    void rightRotate(NodePtr y)
    {
        NodePtr x;

        x = y->left;
        y->left = x->right;
        if (x->right != leafNode)
        {
            x->right->parent = y;
        }
        x->parent = y->parent;

        if (!y->parent)
        {
            root = x;
        }
        else if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }
        y->parent = x;
        x->right = y;
    }

    RBT()
    {
        leafNode = new node;
        leafNode->color = BLACK;
        leafNode->left = nullptr;
        leafNode->right = nullptr;
        leafNode->parent = nullptr;
        root = leafNode;
    }

    NodePtr tree_minimum(NodePtr x)
    {
        while (x->left != leafNode)
        {
            x = x->left;
        }
        return x;
    }
};

int main()
{
	ifstream ifp("rbt.inp");
	ofstream ofp("rbt.out");

    char op;
    int key;
    string color;
    RBT rbt;

    while (true)
    {
        ifp >> op;
        ifp >> key;

        if (key == -1)
            break;

        switch (op)
        {
        case 'i':
            rbt.Insertion(key); break;
        case 'c':
            if (rbt.IsKey(key)->color == RED)
                color = "RED";
            else
                color = "BLACK";

            ofp << "color(" << rbt.IsKey(key)->key << "): " << color << endl; break;
            //cout << "color(" << rbt.IsKey(key)->key << "): " << color << endl; break;
        case 'd':
            rbt.Deletion(key); break;
        }

    }
	ifp.close();
	ofp.close();

    return 0;
}