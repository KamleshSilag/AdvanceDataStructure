//Name : Kamlesh Silag
//Gr no : 172047
//Division : SY-D
//Program : To insert,delete, find k in (logn) time.

#include<stdio.h>
#include<conio.h>
#include<malloc.h>
struct node
{
	struct node *left,*right;
	int key;
	int height;
	int count;
};



int max(int a,int b)
{
	return (a>b) ? a:b;
}

int height(struct node *N)
{
	if(N==NULL)
		return 0;
	return(N->height);
}

int getBalance(struct node *N)
{
	if(N==NULL)
		return 0 ;
	return height(N->left)- height(N->right);
}

struct node* newnode(int key)
{
	struct node *node = (struct node*)malloc(sizeof(struct node));
	node->key=key;
	node->left=NULL;
	node->right=NULL;
	node->height=1;
	node->count=1;
	return node;
}

void displayCount(struct node *N)
{
	if(N!=NULL)
	{
		printf(" %d ",N->key);
		printf("\tCount : %d\n",N->count);
		displayCount(N->left);
		displayCount(N->right);

	}
}

struct node *search(struct node *root,int k)
{
	int flag ;
	if(root->left==NULL)
	     flag=0;
	else
	     flag=root->left->count;


		if(k ==flag+1)
			return(root);
		else if(k<flag+1)
			return(search(root->left,k));
		else if(k>flag+1)
		{
			int temp = flag+1;
			return(search(root->right,k-temp));
		}
}

struct node * minValueNode(struct node* node)
{
    struct node* current = node;
 
    while (current->left != NULL)
        current = current->left;
 
    return current;
}


struct node *rightrotate(struct node *y)
{
	struct node *x=y->left;
	struct node *T2=x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left),height(y->right))+1;
	x->height = max(height(x->left),height(x->right))+1;

	y->count=y->count-x->count+1;
	x->count=y->count+1;
	return x;
}


struct node *leftrotate(struct node *x)
{
	struct node *y,*T2;
	y=x->right;
	T2=y->left;

	y->left=x;
	x->right=T2;

	x->height= max(height(x->left),height(x->right))+1;
	y->height= max(height(y->left),height(y->right))+1;


	x->count=x->count - y->count;
	y->count=y->count+x->count;


	return y;
}


//Deleting element
struct node* deleteNode(struct node* root, int key)
{

    if (root == NULL)
	return root;

    if ( key < root->key )
    {
		root->count--;
		root->left = deleteNode(root->left, key);
    }
	
	else if( key > root->key )
    {
		root->count--;
		root->right = deleteNode(root->right, key);
	}

    else
    {
    	root->count--;
		if( (root->left == NULL) || (root->right == NULL) )
		{
	    	struct node *temp = root->left ? root->left : root->right;

		
		    if (temp == NULL)
	    	{
				temp = root;
				root = NULL;
	    	}
	    	else 
	     		*root = *temp; 
			    
	    	free(temp);
		}
		else
		{
	    	struct node* temp = minValueNode(root->right);

	    	root->key = temp->key;
	    	root->right = deleteNode(root->right, temp->key);
		}
    }

    if (root == NULL)
      return root;

    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    int balance = getBalance(root);
 

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightrotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftrotate(root->left);
        return rightrotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftrotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightrotate(root->right);
        return leftrotate(root);
    }
 
    return root;
}


struct node* insert(struct node* node,int key)
{
	int balance;
	if(node==NULL)
		return (newnode(key));

	else if(key<node->key)
	{
		node->count++;
		node->left=insert(node->left,key);
	}
	else if(key>node->key)
	{
		node->count++;
		node->right=insert(node->right,key);
	}
	else
		return node;

	node->height = 1 + max(height(node->left),height(node->right));

	balance = getBalance(node);

	if(balance>1 && key < node->left->key)
		return rightrotate(node);

	if(balance<-1 && key>node->right->key)
		return leftrotate(node);

	if(balance>1 && key>node->left->key)
	{
		node->left= leftrotate(node->left);
		return rightrotate(node);
	}

	if(balance<-1 && key<node->right->key)
	{
		node->right = rightrotate(node->right);
		displayCount(node);
		return leftrotate(node);
		displayCount(node);
	}

	return node;
}

int main()
{
	struct node *root=NULL,*node=NULL;
	int k,ch=0,val;


	do
	{
		printf("\n1.Insert\n2.Delete\n3.Display\n4.Find K\n5.Exit\n\nEnter your choice:");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1:
				printf("\n Enter data to insert : ");
				scanf("%d",&val);
				root = insert(root,val);
				break;

			case 2:
				printf("\n Enter data to delete :");
				scanf("%d",&val);
				root = deleteNode(root,val);
				break;
			case 3:
				displayCount(root);
				break;
			case 4:
				printf("\nEnter K : ");
				scanf("%d",&k);
				node = search(root,k);
				printf("\nElement : %d\n",node->key);
				break;
		}

		getch();

	}while(ch!=5);
	return 0;

}