/*
	Author: Pranit Chawla
	Roll no: 17EC30026
	Assignment 3: Divide and Conquer 
*/
#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
extern void registerme ( int );
extern void startpart ( int );
extern void endpart ( int );
extern void makemove ( int , int , int );
extern void showpegs ();
void ToH3 (int i,int j,int p,int q,int r) // Solving the 3-peg problem as a sub-routine for further problems
{
	if (j==i)
	{
		makemove(j,p,q); // if only one peg is left, move from 0 to 1
		//makemove(j,0,1);
		return;
	}
	else
	{
		ToH3(i,j-1,p,r,q); 
		makemove(j,p,q);   // normal 3 peg TOH problem
		ToH3(i,j-1,r,q,p);
		// ToH3(i,j-1,0,2,1);
		// makemove(j,0,1);
		// ToH3(i,j-1,2,1,0);
	}
}
void ToH42 (int i,int j,int p,int q,int r,int s,int k)
{
	int tot=j-i+1; // total number of pegs
	if (tot<=k)
	{
		ToH3(i,j,p,q,r); // calling 3 peg toh if n is less than k
		return;
	}
	else
	{
	ToH42(i,j-k,p,s,q,r,k);
	ToH3(j-k+1,j,p,q,r);    // recursive step for 
	ToH42(i,j-k,s,q,p,r,k);
	return;
	}
}
void ToH41 (int i,int j,int p,int q,int r,int s)
{
	int tot=j-i+1;
	if (tot<=3)
	{
	if (tot==1)
	{
		makemove(i,p,q);  // if n is less than or equal to 3, we can list out the moves manually
	}
	else if (tot==2)
	{
		makemove(i,p,r);
		makemove(i+1,p,q);
		makemove(i,r,q);
	}
	else if (tot==3)
	{
		makemove(i,p,s);
		makemove(i+1,p,r);
		makemove(i+2,p,q);
		makemove(i+1,r,q);
		makemove(i,s,q);
	}
	return;
	}
	else
	{
	int k=tot/2;
	ToH41(i,j-k,p,s,q,r);
	ToH3(j-k+1,j,p,q,r);     // recursive step for k=n/2
	ToH41(i,j-k,s,q,p,r);
	return;
	}
}
void ToH43 (int i,int j,int p,int q,int r,int s)
{
	int tot=j-i+1;
	if (tot<=3)
	{
	if (tot==1)
	{
		makemove(i,p,q);
	}
	else if (tot==2)
	{
		makemove(i,p,r);
		makemove(i+1,p,q);     // if n is less than or equal to 3, we can list out the moves manually
		makemove(i,r,q);
	}
	else if (tot==3)
	{
		makemove(i,p,s);
		makemove(i+1,p,r);
		makemove(i+2,p,q);
		makemove(i+1,r,q);
		makemove(i,s,q);
	}
	return;
	}
	else
	{
	int k=sqrt(2*tot);
	ToH43(i,j-k,p,s,q,r);     // recursive step for k=sqrt(2*n)
	ToH3(j-k+1,j,p,q,r);
	ToH43(i,j-k,s,q,p,r);
	return;
	}
}
int main()
{
	int n;
	cin>>n;
	registerme(n);
	startpart(1);
	ToH41(1,n,0,1,2,3);  // calling function with k=n/2
	endpart(1);
	startpart(2);     // calling function in which k=sqrt(n)
	int k=sqrt(n);
	ToH42(1,n,0,1,2,3,k); 
	endpart(2);
	startpart(3);   // calling function in which k=sqrt(2*n)
	ToH43(1,n,0,1,2,3); 
	endpart(3);
}