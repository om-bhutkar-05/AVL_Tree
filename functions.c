#include "header.h"
void init(avl *tree)
{
    *tree = NULL;
}
int height(avl root)
{
    if (root == NULL)
    {
        return 0;
    }
    node *p = root;
return 1 + ((height(p->left) > height(p->right)) ? height(p->left) : height(p->right));
}
node *cnode(int data)
{
    node *nn = (node *)malloc(sizeof(node));
    nn->data = data;
    nn->left = NULL;
    nn->parent = NULL;
    nn->right = NULL;
    return nn;
}
void adjustbf(avl tree)
{
    node *p = tree;
    while (p->parent != NULL)
    {
        p->bf = height(p->left) - height(p->right);
        p = p->parent;
    }
}
void insert(avl *tree, int data)
{
    if (*tree == NULL)
    {
        *tree = cnode(data);
        return;
    }
    node *p = *tree;
    node *q = NULL;
    while (p != NULL)
    {
        q = p;
        if (data < p->data)
        {
            p = p->left;
        }
        else if (data == p->data)
        {
            return;
        }
        else
        {
            p = p->right;
        }
    }
    if (data < q->data)
    {
        q->left = cnode(data);
    }
    else
    {
        q->right = cnode(data);
    }
    adjustbf(q);
    adjustimbalance(*tree,q->parent);
}

void RR(avl *root, avl tree)
{
    if (tree == NULL)
    {
        return;
    }
    node *p = tree;
    node *q = p->right;
    p->right = q->left;
    q->left->parent = p;
    q->left = p;
    q->parent = p->parent;
    p->parent = q;
    if (q->parent)
    {
        if (q->parent->left == p)
        {
            q->parent->left = q;
        }
        else
        {
            q->parent->right = q;
        }
    }
    else
    {
        *root = q;
    }
    adjustbf(tree);
    adjustbf(q);
    return;
}
void LL(avl *root, avl tree)
{
    if (tree == NULL)
    {
        return;
    }
    node *p = tree;
    node *q = p->left;
    p->left = q->right;
    q->right->parent = p;
    q->right = p;
    q->parent = p->parent;
    p->parent = q;
    if (q->parent)
    {
        if (q->parent->left == p)
        {
            q->parent->left == q;
        }
        else
        {
            q->parent->right = q;
        }
    }
    else
    {
        *root = q;
    }
    adjustbf(tree);
    adjustbf(q);
    return;
}

void RL(avl *root, node *n)
{
    RR(root, n->left);
    LL(root, n);
}
void LR(avl *root, node *n)
{
    LL(root, n->right);
    RR(root, n);
}
void adjustimbalance(avl *tree, node *n)
{
    while (n)
    {
        n->bf = height(n->left) - height(n->right);
        if (n->bf < -1)
        {
            if (n->right->bf <= 0)
            {
                RR(tree, n);
            }
            else
            {
                LR(tree, n);
            }
        }
        else if (n->bf > 1)
        {
            if (n->left->bf >= 0)
                LL(tree, n);
            else
            {
                RL(tree, n);
            }
        }
        n=n->parent;
    }
}
void traversal(avl tree){
    if(tree==NULL){
        return;
    }
    node *p=tree;
    traversal(p->left);
    printf("%d ",p->data);
    traversal(p->right);
}
void removenode(avl *tree, int data) {
    if (*tree == NULL) {
        return;
    }
    node *p = *tree;
    node *q = NULL; 
    while (p != NULL && p->data != data) {
        q = p;
        if (p->data > data) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
    if (p == NULL) {
        return; 
    }
    if (p->left == NULL && p->right == NULL) {
        if (q == NULL) {
            free(p);
            *tree = NULL;
        } else if (q->left == p) {
            q->left = NULL;
            free(p);
        } else {
            q->right = NULL;
            free(p);
        }
    } else if (p->left == NULL || p->right == NULL) {
        node *child = (p->left != NULL) ? p->left : p->right;
        if (q == NULL) {
            *tree = child;
            free(p);
        } else if (q->left == p) {
            q->left = child;
            free(p);
        } else {
            q->right = child;
            free(p);
        }
    } else {
        node *successor = p->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        p->data = successor->data;
        removenode(&p->right, successor->data); 
    }
    adjustbf(*tree);
    adjustimbalance(tree, *tree);
}
