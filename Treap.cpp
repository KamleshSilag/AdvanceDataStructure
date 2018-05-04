#include <iostream>
#include<stdlib.h>
using namespace std;

struct TreapNode
{
    int data,priority;
    TreapNode *left,*right;
};

TreapNode *rightRotate(TreapNode *root)
{
    TreapNode *x , *T2;
    x = root->left;
    T2 = x->right;

    x->right = root;
    root->left = T2;

    return x;
}

TreapNode *leftRotate(TreapNode *root)
{
    TreapNode *x , *T2;
    x = root->right;
    T2 = x->left;

    x->left = root;
    root->right = T2;

    return x;
}


TreapNode * insert(TreapNode *root, int data)
{
    if(root ==NULL)
    {
        root = new TreapNode;
        root->data = data;
        root->priority = rand()%100;
        root->left = NULL;
        root->right = NULL;

        return root;
    }

    if(data<root->data) {
        root->left = insert(root->left, data);

        if(root->left->priority> root->priority)
            root = rightRotate(root);
    }
    else
    {
        root->right = insert(root->right,data);

        if(root->right->priority > root->priority)
            root = leftRotate(root);
    }
    return root;


}

TreapNode* search(TreapNode* root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->data == key)
        return root;

    // Key is greater than root's key
    if (root->data < key)
        return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

void traverse(TreapNode *node)
{
    if(node!=NULL)
    {
        traverse(node->left);
        cout<<"Node->data : "<<node->data;
        cout<<"  Node->priority : "<<node->priority<<endl;
        traverse(node->right);
    }
}

int main() {


    TreapNode *root = NULL;
    root = insert(root,10);
    root = insert(root,20);
    root = insert(root,50);
    root = insert(root,23);

    traverse(root);

    if(search(root,60))
    {
        cout<<"\nElement Found";
    }
    else
    {
        cout<<"\nElement not found";
    }

    return 0;
}