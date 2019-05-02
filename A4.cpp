/*
Author: Pranit Chawla 
Dynamic Programming Algorithms 
*/
#include <bits/stdc++.h>
using namespace std;
void realizable (int* A,int n,int T, int** P,int s)
{
	P[0][s]=1;
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<=2*s;j++)
		{
			if ((j-A[i]>=0)&&(j-A[i])<=2*s)
			{
				if (P[i-1][j-A[i]]==1)   // checking if + is possible 
					P[i][j]=1;
			}
			if ((j+A[i])<=2*s&&(j+A[i])>=0)
			{
				if (P[i-1][j+A[i]]==1)   // checking if - is possible 
					P[i][j]=1;
			}
		}
	}
	//cout<<P[n][T+s];
}
void showone (int* A,int n,int T, int** P,int s)
{
	char* arr;
	arr=(char*)malloc((n+1)*(sizeof(char)));
	int k=n;
	int j=T+s;
	for (int i=n;i>=1;i--)
	{
			int f=0;
			if ((j-A[i]>=0)&&(j-A[i])<=2*s)
			{
				if (P[i-1][j-A[i]]==1)
				{
					arr[k]='+';   // checking if + is possible, if yes then change sum to sum-a[i]
					j=j-A[i];
					f=1;
				}
			}
			if (f==0)
			{
			if ((j+A[i])<=2*s&&(j+A[i])>=0)
			{
				if (P[i-1][j+A[i]]==1)
				{
					arr[k]='-';    // checking if + is possible, if yes then change sum to sum+a[i]
					j=j+A[i];
				}
			}
			}
			k--;
	}
	for (int i=1;i<=n;i++)
		cout<<arr[i]<<A[i];
	cout<<"="<<T;
}
void showall (int* A,int n,int T, int** P,int s,int sum,int n_temp,char* arr,int* t)
{
	if (n==0)
	{
		*t=*t+1;
		cout<<"Sol "<<*t<<" ";
		for (int i=1;i<=n_temp;i++)
		cout<<arr[i]<<A[i];
		cout<<"="<<T;
		cout<<endl;
	}
	if (sum-A[n]>=0&&(sum-A[n])<=2*s)
	{
		if (n>=1)
		{
			if (P[n-1][sum-A[n]]==1)
			{
				arr[n]='+';
				//cout<<"check"<<endl;
				showall(A,n-1,T,P,s,sum-A[n],n_temp,arr,t);  // recursively calling the function on n-1 and sum-a[i]
			}
		}
	}
	if (sum+A[n]<=2*s)
	{
		if (n>=1)
		{
			if (P[n-1][sum+A[n]]==1)
			{
				arr[n]='-';
				//cout<<"check"<<endl;
				showall(A,n-1,T,P,s,sum+A[n],n_temp,arr,t);   // recursively calling the function on n-1 and sum-a[i]
			}
		}
	}
}
int main()
{
	int n;
	cout<<"n =";
	cin>>n;
	char* arr;
	arr=(char*)malloc((n+1)*(sizeof(char)));
	int* A;
	A=(int*)malloc((n+1)*sizeof(int));
	int s=0;
	cout<<"The input array:"<<endl;
	for (int i=1;i<=n;i++)
	{
		cin>>A[i];
		s+=A[i];
	}
	int T;
	cout<<"T = ";
	cin>>T;
	int** P;
	P=(int**)malloc((n+1)*sizeof(int*));
	// cout<<"s";
	for (int i=0;i<=n;i++)
		P[i]=(int*)malloc((2*s+1)*sizeof(int));
	for (int i=0;i<=n;i++)
	{
		for (int j=0;j<=2*s;j++)
			P[i][j]=0;
	}
	realizable(A,n,T,P,s);
	cout<<"+++ Part 1: Realizability check"<<endl;
	if (P[n][T+s])
	{
		cout<<"the value "<<T<<" is realizable"<<endl;
		cout<<"+++ Part 2: One solution"<<endl;
		showone(A,n,T,P,s);
		cout<<endl;
		int *t;
		int f=0;
		t=&f;
		cout<<"+++ Part 3: All solutions"<<endl;
		showall(A,n,T,P,s,T+s,n,arr,t);
		cout<<"Number of solutions = ";
		cout<<*t<<endl;
	}
	else
		cout<<"the value "<<T<<" is not realizable"<<endl;
}