#include<iostream.h>
#include<time.h>
#include<stdlib.h>
#include<mem.h>
#include<conio.h>
#include<string.h>
#define MAX 4

class Node
{
	public:
		int key;
		Node **forward;
		Node(int k,int lvl)
		{
			key = k ;
			forward = new Node*[lvl+1];
			memset(forward,0,sizeof(Node *)*(lvl+1));
		}
};

class Skiplist
{
	public :
		int maxlvl, lvl;
		float p;

		Node *header;

		Skiplist(int,float);
		void insert(int);
		void display();
		int randomlvl();
};


int Skiplist::randomlvl()
{
	float r = (float)rand()/RAND_MAX;
	int lvl = 0;

	while(r<p && lvl < maxlvl)
	{
		lvl++;
		r = (float)rand()/RAND_MAX;
	}

	return lvl;
}


Skiplist::Skiplist(int l,float e)
{
	maxlvl = l;
	p = e;
	header = new Node(-1,maxlvl);
	lvl = 0;
}


void Skiplist::display()
{
	for(int i=0;i<=lvl; i++)
	{
		Node *n = header->forward[i];
		cout<<"Level : "<<i;

		while(n!=NULL)
		{
			cout<<"\t  "<<n->key;
			n = n->forward[i];
		}

		cout<<"\n";
	}
}



void Skiplist::insert(int key)
{
	Node *current = header;
	Node *update[MAX+1];
	memset(update,0,sizeof(Node* )* (lvl+1));

	for(int i=lvl;i>=0;i--)
	{
		while(current->forward[i]!=NULL && current->forward[i]->key<key)
		 current = current->forward[i];
		update[i] = current;
	}

	current = current->forward[i];

	if(current==NULL || current->key!=key)
	{
		int rlvl = randomlvl();
		if(lvl < rlvl)
		{
		    for(i=lvl+1;i<rlvl;i++)
			update[i]  = header;
		    lvl = rlvl;
		}

		Node *n = new Node(key,rlvl);
		for(int i=0;i<=rlvl;i++)
		{
			n->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = n;
		}

		cout<<"Inserted Successfully";


	}

}


int main()
{
	Skiplist lst(3,0.5);
	int num,ch;

	do
	{
		cout<<"\n1.Insert\n2.Display\n3.Exit\nEnter your Choice:";
		cin>>ch;

		switch(ch)
		{
			case 1:
				cout<<"\nEnter no :";
				cin>>num;
				lst.insert(num);
				break;

			case 2:
				lst.display();
				break;
		}
	}while(ch!=3);
	return 0;
}