#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define M 1000000000
extern void registerme ( );
extern void startgame ( int );
extern int valquery ( int );
extern int sgnquery ( int );
extern int delquery ( int );
extern int sumquery ( int );
extern void checksoln ( int, int );
void playgame3 () // done in constant time, evaluate function at 0 and mid, we get l+r and r-l solve for l and r
{
	int l=0;
	int r=M-1;
	int left;
	int sum;
	int a1=sumquery(0);
	int mid=a1/2;
	int a2=sumquery(mid);
	checksoln((a1-a2)/2,(a1+a2)/2);
}
void playgame2 () // normal binray search solve the linear equations for l and r
{
	ll l=0;
	ll r=M-1;
	ll ans;
	ll mid;
	int deq=delquery(0);
	while (l<=r)
	{
		if ((l+r)%2==0)
			mid=(l+r)/2;
		else
			mid=(l+r+1)/2;
		int a=sgnquery(mid);
		if (l==r)
		{
			if (a>=0)
				ans=mid;
			else
				ans=mid+1;
			if ((l+r)%2==0)
			{
				int right=(2*ans+deq)/2;
				int left=right-deq;
				checksoln(left,right);
				break;
			}
			else
			{
				int right=(2*ans+deq-1)/2;
				int left=right-deq;
				checksoln(left,right);
				break;
			}
		}
		else if (a==0)
		{
			ans=mid;
			int right=(2*ans+deq)/2;
			int left=right-deq;
			checksoln(left,right);
			break;
		}
		else if (a==1)
		{
				r=mid-1; //recurse on left half
		}
		else if (a==-1)
			l=mid+1;    //recurse on right half
	}

}
void playgame1 (int l, int r,int* f) // divide and conquer algo 
{
		if (l<=r&&*f==1)
		{
		int mid;
		mid=l+(r-l)/2;
		if (valquery(mid)!=mid) // stopping condition of algo
		{
			int left=mid;
			int right=valquery(mid);
			checksoln(left,right);
			*f=0;
			return;
		}
		else
		{
			if (*f==1)
				playgame1(l,mid-1,f); // checking for left half
			if (*f==1);
				playgame1(mid+1,r,f); // checking for right half
		}
	}
}
void playgame0 () // linear search
{
	ll l,r;
	for (ll i=0;i<M;i++)
	{
		if (valquery(i)!=i)
		{
			l=i;
			r=valquery(i);
			break;
		}
	}
	checksoln(l,r);
}
int main()
{
int *f; // used to check playgame1 and stop when true value has been attained
int a=1;
f=&a;
registerme();
startgame(0);
playgame0();
startgame(1);
playgame1(0,M-1,f);
startgame(2);
playgame2();
startgame(3);
playgame3();
}