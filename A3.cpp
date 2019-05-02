/*
	Author: Pranit Chawla
	Roll No: 17EC30026
	Greedy Algorithms
*/
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
typedef long long int ll;
void grdsearch1 (double* p, double* r,int n)
{
	int* ans;
	int* vis;
	double tot=0;
	ans=(int*)malloc(n*sizeof(int));   // storing the permutation
	vis=(int*)malloc(n*sizeof(int));   // keeping a visited array to check which element's maximum has been obtained
	for (int i=0;i<n;i++)
		vis[i]=0;
	for (int j=0;j<n;j++)
	{
		double max_value=-2;  // initiazing to negative value
		int max_index=0;     
		for (int i=0;i<n;i++)
		{
			if (!vis[i])
			{
				double po=pow(r[i],j);
				double t=p[i]*po;
				if (t>max_value)
					{
						max_value=t;   // update step to calculate maximum at each step (greedy)
						max_index=i;
					}
			}
		}
		tot+=max_value;  // calculating the total sum
		vis[max_index]=1; // marking the element chosen as visited
		ans[j]=max_index; // updating the answer array
		cout<<"[ ";
		printf("%d %d %0.6lf",j,max_index,max_value);
		cout<<" ]";
		cout<<endl;
	}
		cout<<"--- Total cost = ";
		printf("%0.6lf",tot);
		cout<<endl;
}
// the comments for grdsearch2 and grdsearch 3 are the same as 1 and hence have been skipped
void grdsearch2 (double* p, double* r,int n) // same as grdsearch1 excpet that we calculate minimum at each step
{
	int* ans;
	int* vis;
	double tot=0;
	double* val;
	val=(double*)malloc(n*sizeof(double));
	ans=(int*)malloc(n*sizeof(int));
	vis=(int*)malloc(n*sizeof(int));
	for (int i=0;i<n;i++)
		vis[i]=0;
	for (int j=n-1;j>=0;j--)
	{
		double min_value=INT_MAX;
		int min_index;
		for (int i=0;i<n;i++)
		{
			if (!vis[i])
			{
				double po=pow(r[i],j);
				double t=p[i]*po;
				if (t<min_value)
					{
						min_value=t;
						min_index=i;
					}
			}
		}
		vis[min_index]=1;
		tot+=min_value;
		ans[j]=min_index;
		val[j]=min_value;
	}
	for (ll i=0;i<n;i++)
	{
		cout<<"[ "<<i<<" "<<ans[i]<<" ";
		printf("%0.6lf",val[i]);
		cout<<" ]";
		cout<<endl;
	}	
	cout<<"--- Total cost = ";
	printf("%0.6lf\n",tot);
}
void grdsearch3 (double* p, double* r,int n)  // using a different heuristic
{
	int* ans;
	int* vis;
	double tot=0;
	double* val;
	val=(double*)malloc(n*sizeof(double));
	ans=(int*)malloc(n*sizeof(int));
	vis=(int*)malloc(n*sizeof(int));
	for (int i=0;i<n;i++)
		vis[i]=0;
	for (int j=0;j<n-1;j++)
	{
		double max_value=-2;
		int max_index;
		for (int i=0;i<n;i++)
		{
			if (!vis[i])
			{
				double po1=pow(r[i],j);
				double po2=pow(r[i],j+1);
				double t=p[i]*(po2-po1);
				if (t>max_value)
					{
						max_value=t;
						max_index=i;
					}
			}
		}
		double temp1,temp2;
		temp1=p[max_index];
		temp2=pow(r[max_index],j);
		temp1=temp1*temp2;
		tot+=temp1;
		vis[max_index]=1;
		val[j]=temp1;
		ans[j]=max_index;
		//cout<<max_index<<endl;
	}
	// for (ll i=0;i<n;i++)
	// 	cout<<vis[i]<<" ";
	int left;
	for (ll i=0;i<n;i++)
	{
		if (!vis[i])
		{
			left=i;
			vis[left]=1;
			double temp1,temp2;
			temp1=p[left];
			temp2=pow(r[left],n-1);
			temp1=temp1*temp2;
			val[n-1]=temp1;
			ans[n-1]=left;
			tot+=temp1;
			break;
		}
	}
	for (ll i=0;i<n;i++)
	{
		cout<<"[ "<<i<<" "<<ans[i]<<" ";
		printf("%0.6lf",val[i]);
		cout<<" ]";
		cout<<endl;
	}
	cout<<"--- Total cost = ";
	printf("%0.6lf\n",tot);

}
void exhsearch(int* P, int n,int k,double* p,double *r, double* min_value,int* ans)
{
	int i,t,u;
	double ti=0;
	for (i=0;i<k;i++)    // PRUNING CONDITION, checking if the value till k has exceeded the min value, in which case we return
	{
		double x=pow(r[P[i]],i);
		ti+=(p[P[i]]*x);
		if (ti>=*min_value)
			return;
	}
	if (k == n) // new permutation has been generated, working on it in this block
	{
		double t=0;
		for (int j=0;j<n;j++)
		{
			double x=pow(r[P[j]],j);
			t+=(p[P[j]]*x);
		}
		// cout<<t<<" "<<*min_value<<endl;
		if (t<*min_value)   // if this permutation gives better answer as compared to minimum so far, update minimum
		{
			*min_value=t; // update the min value
			for (int i=0;i<n;i++)
				ans[i]=P[i];  // update the answer permutation
		}
		return;
	}
	for (i=k;i<n;i++)
	{
		t=P[k];
		P[k]=P[i];  //swapping P[k] and P[i] 
		P[i]=t;
		exhsearch(P,n,k+1,p,r,min_value,ans);  // recursive step
		u=P[k];
		P[k]=P[i];  //swapping P[k] and P[i] 
		P[i]=u;
	}
}
int main()
{
	cout<<"n = ";
	int n;
	cin>>n;
	double* p;
	double* r;
	int* ans;
	double* min_value;
	double m=INT_MAX;
	min_value=&m;
	int* P;
	ans=(int*)malloc(n*sizeof(int));
	p=(double*)malloc(n*sizeof(double));
	r=(double*)malloc(n*sizeof(double));
	P=(int*)malloc(n*sizeof(int));
	cout<<"Initial Prices "<<endl;
	for (int i=0;i<n;i++)
		cin>>p[i];
	cout<<"Appreciation rates"<<endl;
	for (int i=0;i<n;i++)
		cin>>r[i];
	cout<<"+++ Greedy search 1"<<endl;
	grdsearch1(p,r,n);
	cout<<endl;
	cout<<"+++ Greedy search 2"<<endl;
	grdsearch2(p,r,n);
	cout<<endl;
	cout<<"+++ Greedy search 3"<<endl;
	grdsearch3(p,r,n);
	cout<<endl;
	for (int i=0;i<n;i++)
		P[i]=i;
	if (n<=12)
	{
		exhsearch(P,n,0,p,r,min_value,ans);
		double tot=0;
		cout<<"+++ Exhaustive search"<<endl;
		for (int i=0;i<n;i++)
		{
			cout<<"[ "<<i<<" "<<ans[i]<<" ";
			double a,b;
			a=pow(r[ans[i]],i);
			b=a*p[ans[i]];
			tot+=b;
			printf("%0.6lf",b);
			cout<<" ]"<<endl;
		}
		cout<<"--- Total cost = ";
		printf("%0.6lf\n",tot);
	}
	else
	{
		cout<<"+++ Exhaustive search"<<endl;
		cout<<"*** n is too large, skipping exhaustive search"<<endl;
	}
	
}