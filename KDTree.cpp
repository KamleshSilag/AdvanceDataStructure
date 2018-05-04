/*
 * Created By Kamlesh Silag on 09/04/2018
 * Program : KDtree implementation
*/ 

#include<iostream>
using namespace std;

const int k = 2;

struct KDNode
{
	int points[k];
	KDNode *left,*right;
};

KDNode* insert(KDNode *root,int points[],unsigned depth)
{
	if(root==NULL)
	{
		root = new KDNode;
		for(int i=0;i<k;i++)
			root->points[i]=points[i];

		root->left=root->right =NULL;
		return root;
	}

	unsigned cd = depth % k;

	if(points[cd]  < root->points[cd])
	{
		root->left = insert(root->left,points,depth+1);
	}
	else
	{
		root->right = insert(root->right,points,depth+1);
	}

	return root;
}

bool arepointssame(int point1[],int point2[])
{
	for(int i=0;i<k;i++)
	{
		if(point1[i]!=point2[i])
			return false;
	}
	return true;
}

KDNode * search(KDNode *root,int points[],unsigned depth)
{
	if(root==NULL)
		return root;
	if(arepointssame(root->points,points))
		return root;

	unsigned cd = depth % k;

	if(points[cd] < root->points[cd])
		return search(root->left,points,depth+1);
	return search(root->right,points,depth+1);

}

void traverse(KDNode *node , int points[][k])
{
	if(node!=NULL)
	{
		
		traverse(node->left,points);
		
		for(int i=0;i<k;i++)
		{
			cout<<node->points[i]<<" ";
		}
		cout<<"\n";
		traverse(node->right,points);
		
	}
}

int main()
{

	KDNode *root = NULL;
	int points[][k] = {{1,5},{3,9},{6,5},{4,8}};

	int n =sizeof(points)/sizeof(points[0]);

	for(int i=0;i<n;i++)
	{
		root = insert(root,points[i],0);
	}

	traverse(root,points);

	int point1[] = {3,9};

	if(search(root,point1,0))
		cout<<"point found";
	else
		cout<<"point not found";

return 0;
}