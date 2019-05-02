#include <bits/stdc++.h>
using namespace std;
typedef struct 
{
	int l,r;
}interval;
typedef struct 
{
	int endpoint;
	int number;
	int lor;
}end;
int DeleteQ (int* Q,interval* in, int* idx,end* E, int size,int k)
{
	int l=idx[E[k].number];
	if (l==size-1)
	{
		size--;
		return (size);
	}
	else
	{
		size--;
		Q[l]=Q[size-1];
		idx[Q[l]]=idx[Q[size-1]];
		int i=l;
		while (i!=0&&in[Q[i]].r > in[Q[(i-1)/2]].r) 
    { 
       swap(Q[i],Q[(i-1)/2]);
       swap(idx[Q[i]],idx[Q[(i-1)/2]]);
       i = ((i-1)/2); 
       // if (i<0)
       // 	break;
    } 
		return (size);
	}
}
int InsertQ (int* a,interval* in,int* idx,int val, int n)
{
	n++;
	a[n-1]=val;
	idx[val]=n-1;
	int i=n-1;
	 while (i!=0&&in[a[i]].r > in[a[(i-1)/2]].r) 
    { 
       swap(a[i],a[(i-1)/2]);
       swap(idx[a[i]],idx[a[(i-1)/2]]);
       i = ((i-1)/2); 
       // if (i<0)
       // 	break;
    } 
	return n;
}
void merge (end *S,int low,int high,int mid)
{
	int i=low;
	int j=mid+1;
	end *temp;
	temp=(end*)malloc(sizeof(end)*(high-low+1));
	for (int k=0;k<high-low+1;)
	{
		if (i>mid)
			temp[k++]=S[j++];
		else if (j>high)
			temp[k++]=S[i++];
		else
		{
			if (S[j].endpoint<S[i].endpoint)
				temp[k++]=S[j++];
			else
				temp[k++]=S[i++];
		}
	}
		for (int k=0;k<high-low+1;k++)
			S[low+k]=temp[k];
}
void merge_sort (end* S,int low, int high)
{
	if (low<high)
	{
		int mid=(low+high)/2;
		merge_sort(S,low,mid);
		merge_sort(S,mid+1,high);
		merge(S,low,high,mid);
	}
}
void mincover (interval* in, int n, int L,int R)
{
	end* E;
	E=(end*)malloc(sizeof(end)*(2*n+1));
	//end E[2*n+1];
	int k=0;
	for (int i=0;i<n;i++)
	{
		E[k].endpoint=in[i].l;
		E[k].number=i;
		E[k].lor=0;
		k++;
		E[k].endpoint=in[i].r;
		E[k].number=i;
		E[k].lor=1;
		k++;
	}
	merge_sort(E,0,2*n-1);
	// for (int i=0;i<2*n;i++)
	// 	cout<<E[i].endpoint<<" "<<E[i].number<<endl;
	int* Q;
	Q=(int*)malloc(sizeof(int)*(n+1));
	int* idx;
	int total=0;
	idx=(int*)malloc(sizeof(int)*(n+1));
	for (int i=0;i<n;i++)
		idx[i]=-1;
	int size=0;
	//size=InsertQ(Q,in,idx,E[0].number,size);
	Q[0]=E[0].number;
	total++;
	idx[Q[0]]=0;
	size++;
	k=0;
	int x=in[E[0].number].r;
	//idx[E[0].number]=0;
	cout<<"Added Interval "<<Q[0]<<" "<<in[Q[0]].l<<" "<<in[Q[0]].r<<endl;
	while (x<R)
	{
		k++;
		//cout<<"check"<<endl;
		if (E[k].endpoint==in[E[k].number].l) 
		{
			size=InsertQ(Q,in,idx,E[k].number,size);
			//idx[E[k].number]=size-1;
		} 
		else
		{
			size=DeleteQ(Q,in,idx,E,size,k);
		if (E[k].endpoint==x)
		{
			cout<<"Added Interval "<<Q[0]<<" "<<in[Q[0]].l<<" "<<in[Q[0]].r<<endl;
			total++;
			x=in[Q[0]].r;
		}
		}
	}
	cout<<"total number of intervals: "<<total<<endl;
}
int main()
{
	int n;
	cin>>n;
	interval* in;
	in=(interval*)malloc(sizeof(interval)*(n));
	for (int i=0;i<n;i++)
	{
		cin>>in[i].l>>in[i].r;
	}
	mincover(in,n,0,999);
}