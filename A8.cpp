#include <bits/stdc++.h>
using namespace std;
struct tree
{
	struct tree* parent;
	int size;
};
typedef struct tree tree;
tree** initsets (int n)
{
	tree** t=(tree**)malloc(sizeof(tree*)*(n+1));
	for (int i=0;i<=n;i++)
	t[i]=(tree*)malloc(sizeof(tree)*n);
	for (int i=0;i<=n;i++)
	{
		for (int j=0;j<n;j++)
		{
			t[i][j].size=1;
			t[i][j].parent=NULL;
		}
	}
	return t;
}
tree* findset (tree** t,int i,int j)
{
	tree* p=t[i][j].parent;
	tree* temp=&t[i][j];
	while (p!=NULL)
	{
		temp=p;
		p=p->parent;
	}
	return temp;
}
void mergesets (tree* p,tree* q)
{
	if (p!=q)
	{
		if ((p->size)<(q->size))
		{
			p->parent=q;
			(q->size)=(q->size)+(p->size);
		}
		else
		{
			q->parent=p;
			(p->size)=(p->size)+(q->size);
		}
	}
}
bool isvalid (int i,int j,int n)
{
	if (i>=0&&j>=0&&i<=n&&j<=n-1)
		return true;
	else
		return false;
}
bool mergeregions (tree** t,int** a,int n)
{
	for (int i=0;i<=n;i++)
	{
		for (int j=0;j<n;j++)
		{
			tree* p=findset(t,i,j);
			if (a[i][j])
			{
				if (isvalid(i+1,j,n))
				{
					if (a[i+1][j])
					{
						tree* q=findset(t,i+1,j);
						mergesets(p,q);
					}
				}
				if (isvalid(i-1,j,n))
				{
					if (a[i-1][j])
					{
						tree* q=findset(t,i-1,j);
						mergesets(p,q);
					}
				}
				if (isvalid(i,j-1,n))
				{
					if (a[i][j-1])
					{
						tree* q=findset(t,i,j-1);
						mergesets(p,q);
					}
				}
				if (isvalid(i,j+1,n))
				{
					if (a[i][j+1])
					{
						tree* q=findset(t,i,j+1);
						mergesets(p,q);
					}
				}
			}
		}
	}
	int f=0;
	for (int i=0;i<n;i++)
	{
		tree* root1=findset(t,n,i);
		tree* root2=findset(t,0,0);
		if (root1!=NULL&&root2!=NULL)
		{
			if (root1==root2)
				f=1;
		}
	}
	return f;
}
void print_pattern (int** a,int n)
{
	for (int i=0;i<=n;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (a[i][j])
				cout<<"  ";
			else
				cout<<"X ";
		}
		cout<<endl;
	}
}
void findreach (tree** t,int** a,int n)
{
	tree* root1=findset(t,0,0);
	for (int i=0;i<=n;i++)
	{
		for (int j=0;j<n;j++)
		{
			tree* root2=findset(t,i,j);
			if (a[i][j])
			{
			if (root1==root2)
				cout<<"- ";
			else
				cout<<"  ";
			}
			else
				cout<<"X ";
		}
		cout<<endl;
	}
}
int main()
{
	int n;
	cin>>n;
	// int a[n+1][n];
	int** a=(int**)malloc(sizeof(int*)*(n+1));
	for (int i=0;i<=n;i++)
		a[i]=(int*)malloc(sizeof(int)*n);
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<n;j++)
		{
			cin>>a[i][j];
		}
	}
	for (int i=0;i<n;i++)
		a[0][i]=1;
	tree** t;
	t=initsets(n);
	bool result;
	cout<<"+++ Input mesh"<<endl;
	print_pattern(a,n);
	cout<<endl;
	result=mergeregions(t,a,n);
	if (result)
		cout<<"+++ Liquid can seep through the mesh"<<endl;
	else
		cout<<"+++ Liquid cannot seep through the mesh"<<endl;
	cout<<endl;
	cout<<"+++ Reachable cells in the mesh"<<endl;
	cout<<endl;
	findreach(t,a,n);
}