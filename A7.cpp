#include <bits/stdc++.h>
#include "BB7.h"
using namespace std;
BST rrotate (BST root)
{
	BST temp;
	temp=root->L;
	BST M=temp->R;
	temp->R=root;
	root->L=M;
	return temp;
}
BST lrotate (BST root)
{
	BST temp;
	temp=root->R;
	BST M=temp->L;
	temp->L=root;
	root->R=M;
	return temp;
}
BST unskew (BST* A,int size,BST t)
{
	BST r=t->R;
	for (int i=size-1;i>=0;i--)
	{
		A[i]->R=lrotate(A[i]->R);
		r=A[i]->R;
	}	
	return r;
}
BST rightskew (BST p,BST* A,int* t)
{
	BST q=p->R;
	BST r=NULL;
	while (1)
	{
		if (q->L==NULL&&q->R==NULL)
			break;
		else if (q->L==NULL&&q->R!=NULL)
		{
			if (r==NULL)
				r=p;
			p=p->R;
			q=q->R;
		}
		else
		{
			A[(*t)++]=p;
			p->R=rrotate(q);
			q=p->R;
		}
	}
	return r;
}
void preorder (BST root)
{
	if (root!=NULL)
	{
		cout<<root->key<<" ";
		preorder(root->L);
		preorder(root->R);
	}
}
void find_corr (BST* A,BST* B,BST a,int size)
{
	BST temp1=a;
	int i=0;
	int k=0;
	for (int i=0;i<size;i++)
	{
		while (temp1->key!=A[i]->key)
			temp1=temp1->R;
		B[i]=temp1;
	}
}

int main()
{
	BST S, T;
	int n;
	cin>>n;
	registerme(n); 
	S = getsourcetree();
	T = gettargettree();
	BST p1,p2;
	p1=(BST)malloc(sizeof(BST));
	p1->key=INT_MIN;
	p1->L=NULL;
	p1->R=S;
	p2=(BST)malloc(sizeof(BST));
	p2->key=INT_MIN;
	p2->L=NULL;
	p2->R=T;
	BST list1,list2;
	BST* hsource=(BST*)malloc((n+1)*sizeof(BST));
	BST* htarget=(BST*)malloc((n+1)*sizeof(BST));
	int h_s=0;
	int h_t=0;
	cout<<"Inital Trees : "<<endl;
	cout<<"Source : ";
	preorder(S);
	cout<<endl;
	cout<<"Target : ";
	preorder(T);
	cout<<endl;
	cout<<"Right Skewing the trees : "<<endl;
	list1=rightskew(p1,hsource,&h_s);
	list2=rightskew(p2,htarget,&h_t);
	cout<<"Source : ";
	preorder(list1->R);
	cout<<endl;
	cout<<"Number of Rotations :"<<h_s<<endl;
	cout<<"Target : ";
	preorder(list2->R);
	cout<<endl;
	cout<<"Number of Rotations :"<<h_t<<endl;
	cout<<"Finding node correspondance ";
	BST* hnewsource=(BST*)malloc((n+1)*sizeof(BST));
	find_corr(htarget,hnewsource,list1,h_t);
	BST f1,f2;
	cout<<endl;
	cout<<"Reversing the Skewing Process : ";
	cout<<endl;
	f1=unskew(htarget,h_t,list2);
	f2=unskew(hnewsource,h_t,list1);
	cout<<"Source : ";
	preorder(f1);
	cout<<endl;
	cout<<"Target : ";
	preorder(f2);
	cout<<endl;
}