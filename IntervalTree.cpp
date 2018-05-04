//
// Created by Kamlesh on 03/05/2018.
// Program : Interval Tree

#include <iostream>
using namespace std;

struct IntervalNode
{
    int low,high;
    int maxendpoint;
    IntervalNode *left,*right;
};

IntervalNode * insert(IntervalNode *node,int low,int high)
{
    if(node==NULL)
    {
        node = new IntervalNode;
        node->low = low;
        node->high= high;
        node->left = NULL;
        node->right = NULL;
        node->maxendpoint = high;
        return node;
    }
    if(low<node->low)
    {
        node->left = insert(node->left,low,high);
        if(node->left->maxendpoint > node->maxendpoint)
            node->maxendpoint = node->left->maxendpoint;
    }
    else
    {
        node->right = insert(node->right,low,high);
        if(node->right->maxendpoint > node->maxendpoint)
            node->maxendpoint = node->right->maxendpoint;
    }

    return node;

}


IntervalNode * search(IntervalNode *root,int low,int high)
{
    if(root==NULL || (root->low==low && root->high==high))
    {
        return root;
    }
    if(root->low > low)
    {
        return search(root->left,low,high);
    }
    else
    {
        return search(root->right,low,high);
    }
}

void traverse(IntervalNode *node)
{
    if(node!=NULL)
    {
        traverse(node->left);
        cout<<"node->low :"<<node->low<<" node->high:"<<node->high <<" max :"<<node->maxendpoint<<endl;
        traverse(node->right);
    }
}
int main()
{
    IntervalNode *root =NULL;
    root = insert(root,17,19);
    root = insert(root,5,8);
    root = insert(root,21,24);
    root = insert(root,4,8);
    root = insert(root,15,18);
    root = insert(root,7,10);

    traverse(root);

    if(search(root,7,10))
    {
        cout<<"Interval found";
    }
    else
    {
        cout<<"Interval not found";
    }

    return 0;
}
