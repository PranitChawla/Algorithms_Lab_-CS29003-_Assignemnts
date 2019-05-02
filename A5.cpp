/*
Author: Pranit Chawla 
Roll no: 17EC30026	
Stacks, Queues and Trees 
*/
#include <bits/stdc++.h>
using namespace std;
#include "BB5.h"
typedef struct {
STACK F, B;
} QUEUE;
void TPRNL (struct _treenode* root)  // print the tree level by level after making the pointers point 
{
	while (root!=NULL)
		{
			cout<<root->key<<" ";
			root=root->N;
		}
}
int height(struct _treenode* node) // calculate the height of the tree by passing root and going to leaf
{ 
    if (node==NULL) 
        return 0; 
    else
    { 
        int lheight = height(node->L); 
        int rheight = height(node->R); 
        if (lheight > rheight) 
            return(lheight+1); 
        else return(rheight+1); 
    } 
} 
struct _treenode* SETL(struct _treenode* root, int level,struct _treenode* prev) 
{ 
    if (root == NULL) 
        return prev; 
    if (level == 1) // if level is one then we have reached a particular node, so add that to the list by making prev->N point to it
    {
       	if (prev!=NULL)
       	{
        prev->N=root;
        prev=root;
    	}
        else
        prev=root;
    	return prev;
        //printf("%d ", root->key); 
    }
    else if (level > 1) 
    { 
        prev=SETL(root->L, level-1,prev); // recurse on left and right child 
        prev=SETL(root->R, level-1,prev); 
    } 
} 
struct _treenode* SETN(struct _treenode* root) // calling the function for each level and then recursing on that level
{ 
    struct _treenode *prev;
    prev=NULL;
    int h = height(root); 
    int i; 
    for (i=1; i<=h; i++) 
        prev=SETL(root, i,prev); 
    return root;
} 

void QPRN (QUEUE q) // printing the queue 
{
	SPRNT2B(q.F); // first print the first stack top to down
	SPRNB2T(q.B); // then print second stack down to top
}
QUEUE DEQUEUE (QUEUE q)
{
	if (!ISEMPTY(q.F)) //if F is not empty just pop from F
		q.F=POP(q.F);
	else if (ISEMPTY(q.F)&&!ISEMPTY(q.B)) // first fill all elements in F and then pop top of F
	{
		while (!ISEMPTY(q.B))
		{
			int temp=TOP(q.B);
			q.B=POP(q.B);
			q.F=PUSH(q.F,temp);
		}
		q.F=POP(q.F);
	}
	else if (ISEMPTY(q.F)&&ISEMPTY(q.B)) // dont pop if both are empty i.e queue is empty
			{

			}
	return q;
}
QUEUE ENQUEUE (QUEUE q,int x) // push in B stack
{
	q.B=PUSH(q.B,x);
	return q;
}
QUEUE QINIT ()  // initialise the queue with two empty stacks
{
	QUEUE temp;
	temp.F=SINIT();
	temp.B=SINIT();
	return temp;
}
int main()
{
	registerme();
	int n;
	cout<<"n = ";
	cin>>n;
	cout<<" +++ PART 1 "<<endl;
	QUEUE q;
	q=QINIT();
	cout<<"QINIT()      :Q = [ ]"<<endl;
	int en=0;
	int de=0;
	while (1)
	{
		int num=rand()%1000+1;
		int c=num%2;
		if (en==n)
		{
			de++;
			cout<<"DEQUEUE() : Q = [";
			q=DEQUEUE(q);
			QPRN(q);
			cout<<" ]";
			cout<<endl;
		}
		else if (c==0)
		{
			en++;
			cout<<"ENQUEUE("<<num<<") : Q = [";
			// int num=rand()%1000+1;
			q=ENQUEUE(q,num);
			QPRN(q);
			cout<<" ]";
			cout<<endl;
		}
		else
		{
			if (ISEMPTY(q.B)&&ISEMPTY(q.F))
			{
				continue;
			}
			else
			{
			de++;
			cout<<"DEQUEUE() : Q = [";
			q=DEQUEUE(q);
			QPRN(q);
			cout<<" ]";
			cout<<endl;
			}
		}
		if (en>=n&&de>=n)
			break;
	}
	cout<<endl;
	cout<<"+++ Part 2"<<endl;
	cout<<"--- Generated Tree"<<endl;
	struct _treenode* T;
	T = TGEN(n);
	TPRN(T);
	cout<<endl;
	T=SETN(T);
	cout<<"--- Level-by-level printing"<<endl;
	TPRNL(T);
}