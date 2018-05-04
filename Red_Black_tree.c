//Assignment no 2 (ADS): RBTree Operations - Insertions , Deletions , Searching 
//Name : Kamlesh Silag
//Grno : 172047
//Div : SY-D (Rno : 53)

#include<stdio.h>
#include<stdlib.h>
struct node
{
	struct node *left,*right,*parent;
	int info;
	enum {red,black}color;
};

void insert_Node(int);
void insert_NodeBalance(struct node *);

void rotateLeft(struct node *);
void rotateRight(struct node *);

struct node *succ(struct node *);
void inorder(struct node *);


void del(int n);
void del_balance(struct node *ptr);

void display(struct node *ptr,int level);
int find(int item,struct node **loc);

struct node *root,*nullNode;

int main()
{
	int ch,num;
	struct node *ptr;
	nullNode = (struct node *)malloc(sizeof(struct node));
	nullNode->info= -1;
	nullNode->color = black;
	root = nullNode;


	do
	{

		printf("\n\n1.Insert\n2.Delete\n3.Inorder Traversal\n4.Search\n5.Exit\nEnter your choice:  ");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1:
				printf("\nEnter Value to Insert : ");
				scanf("%d",&num);
				insert_Node(num);
				break;

			case 2:
				printf("\nEnter Value to Delete : ");
				scanf("%d",&num);
				del(num);
				break;	

			case 3:
				inorder(root);
				break;

			case 5:
				exit(0);

			case 4: 
				printf("\nEnter Item to Search : ");
				scanf("%d",&num);
				if(!find(num,&ptr))
					printf("\nItem not found\n");
				else
					printf("\nItem Present\n");
				break;
		}

	}while(1);

	
}
int find(int item,struct node **loc)
{
	struct node *ptr;
	if(root==nullNode)
	{
		*loc=nullNode;
		return 0;
	}

	if(item==root->info)
	{
		*loc=root;
		return 1;
	}

	if(item<root->info)
		ptr=root->left;
	else
		ptr=root->right;

	while(ptr!=nullNode)
	{
		if(item==ptr->info)
		{
			*loc=ptr;
			return 1;
		}

		if(item<ptr->info)
			ptr=ptr->left;
		else
			ptr=ptr->right;
	}

	*loc=nullNode;
	return 0;
}

void insert_Node(int key)
{
	struct node *temp,*par,*ptr;
	par = nullNode ;
	ptr = root ; 

	while(ptr!=nullNode)
	{
		par = ptr;
		if(key < ptr->info )
			ptr = ptr->left;
		else if(key > ptr->info )
			ptr = ptr->right;
		else
		{
			printf("\nDuplicate key");
			return ;
		}
	}

	temp = (struct node *)malloc(sizeof(struct node));
	temp->info = key;
	temp->left = nullNode;
	temp->right= nullNode;
	temp->color = red;
	temp->parent = par;

	if(par==nullNode)
		root = temp;
	else if(temp->info  < par->info)
		par->left = temp;
	else
		par->right = temp;

	insert_NodeBalance(temp);
}


void insert_NodeBalance(struct node *nptr)
{
	struct node *uncle,*grandpa,*par;
	while(nptr->parent->color == red)
	{
		par = nptr->parent;
		grandpa = par->parent;

		if(par==grandpa->left)
		{
			uncle = grandpa->right;
			if(uncle->color ==red )
			{
				uncle->color = black;
				par->color = black;
				grandpa->color=red;
				nptr = grandpa;
			}
			else 
			{
				if(nptr== par->right)
				{
					rotateLeft(par);
					nptr = par;
					par = nptr->parent;
				}

				par->color = black ; 
				grandpa->color= red;
				rotateRight(grandpa);
			}
		}

		else
		{
			if(par==grandpa->right)
			{
				uncle = grandpa->left;
				if(uncle->color == red)
				{
					uncle->color = black;
					par->color = black;
					grandpa->color = red;
					nptr = grandpa;
				}

				else
				{
					if(nptr == par->left)
					{
						rotateRight(par);
						nptr = par;
						par = nptr->parent;
					}
					par->color = black;
					grandpa->color = red;
					rotateLeft(grandpa);
				}
			}
		}
	}

	root->color=black;
}


void del(int item)
{
	struct node *child,*ptr,*successor;
	if(!find(item,&ptr))
	{
		printf("Item Not present ..");
		return ;
	}

	if(ptr->left!=nullNode || ptr->right!=nullNode)
	{
		successor = succ(ptr);
		ptr->info = successor->info;
		ptr=successor;
	}

	if(ptr->left !=nullNode)
		child = ptr->left;

	else
		child = ptr->right;

	child->parent = ptr->parent;

	if(ptr->parent == nullNode)
		root = child;

	else if(ptr == ptr->parent->left)
		ptr->parent->left = child;

	else
		ptr->parent->right = child;

	if(child==root)
		child->color=black;

	else if(ptr->color==black)
	{
		if(child!=nullNode)
			child->color=black;
		else
			del_balance(child);
	}
}


void del_balance(struct node *nptr)
{
	struct node *sib;
	while(nptr!=root)
	{
		if(nptr== nptr->parent->left)
		{
			sib = nptr->parent->right;

			if(sib->color==red)
			{
				sib->color=black;
				nptr->parent->color=red;
				rotateLeft(nptr->parent);
				sib = nptr->parent->right;
			}

			if(sib->left->color==black && sib->right->color==black)
			{
				sib->color=red;
				if(nptr->parent->color==red)
				{
					nptr->parent->color=black;
					return;
				}
				else
					nptr=nptr->parent;
			}

			else
			{
				if(sib->right->color==black)
				{
					sib->left->color=red;
					sib->color=red;
					rotateRight(sib);
					sib = nptr->parent->right;
				}

				sib->color=nptr->parent->color;
				nptr->parent->color = black;
				sib->right->color=black;
				rotateLeft(nptr->parent);
				return;
			}
		}

		else
		{
			sib = nptr->parent->left;
			if(sib->color==red)
			{
				sib->color=black;
				nptr->parent->color=red;
				rotateRight(nptr->parent);
				sib = nptr->parent->left;
			}

			if(sib->right->color==black &&  sib->left->color==black)
			{
				sib->color=red;
				if(nptr->parent->color==red)
				{
					nptr->parent->color=black;
					return;
				}
				else
					nptr=nptr->parent;
			}
			else
			{
				if(sib->left->color==black)
				{
					sib->right->color=black;
					sib->color=red;
					rotateLeft(sib);
					display(root,1);
					sib = nptr->parent->left;
				}

				sib->color=nptr->parent->color;
				nptr->parent->color=black;
				sib->left->color=black;
				rotateRight(nptr->parent);
				return ;
			}
		}

	}
}


struct node *succ(struct node *loc)
{
	struct node *ptr=loc->right;
	while(ptr->left!=nullNode)
		ptr=ptr->left;
	return ptr;
}

void display(struct node *ptr,int level)
{
	int i;
	if(ptr!=nullNode)
	{
		display(ptr->right,level+1);
		printf("\n");
		for(i=0;i<level;i++)
		{
			printf("     ");
		}
		printf("%d \n",ptr->info);
		if(ptr->color==red)
			printf("^");
		else
			printf("*");
		display(ptr->left,level+1);
	}
}

void rotateLeft(struct node *pptr)
{
	struct node *aptr;
	aptr= pptr->right;

	pptr->right = aptr->left;

	if(aptr->left!=nullNode)
		aptr->left->parent=pptr;
	aptr->parent = pptr->parent;

	if(pptr->parent==nullNode)
		root = aptr;
	else if(pptr== pptr->parent->left)
		pptr->parent->left = aptr;
	else
		pptr->parent->right=aptr;

	aptr->left = pptr;
	pptr->parent=aptr;
}


void rotateRight(struct node *pptr)
{
	struct node *aptr;
	aptr = pptr->left;
	pptr->left= aptr->right;

	if(aptr->right!=nullNode)
		aptr->right->parent=pptr;
	aptr->parent =pptr->parent;

	if(pptr->parent==nullNode)
		root=aptr;
	else if(pptr== pptr->parent->right)
		pptr->parent->right=aptr;
	else
		pptr->parent->left=aptr;

	aptr->right = pptr;
	pptr->parent=aptr;

}


void inorder(struct node *ptr)
{
	if(ptr!=nullNode)
	{
		inorder(ptr->left);
		printf("%d  ",ptr->info);
		if(ptr->color==1)
			printf("- BLACK\n");
		else
			printf("- RED\n");
		inorder(ptr->right);
	}
}

