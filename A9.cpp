#include <bits/stdc++.h>
using namespace std;
struct pairs
{
	int x,y;
};
typedef struct pairs pairs;
struct grid {
	int** h;
	int** v;
	pairs** p; 
};
typedef struct grid grid;
bool isvalid (int i,int j,int m,int n)
{
	if (i>=0&&i<m&&j>=0&&j<n)
		return true;
	else
		return false;
}
grid initbhul (int m,int n)
{
	int** hi;
	int** ve;
	pairs** pa;
	hi=(int**)malloc((m-1)*sizeof(int*));
	for (int i=0;i<m-1;i++)
		hi[i]=(int*)malloc(n*sizeof(int));
	ve=(int**)malloc((m)*sizeof(int*));
	for (int i=0;i<m;i++)
		ve[i]=(int*)malloc((n-1)*sizeof(int));
	pa=(pairs**)malloc(m*sizeof(pairs*));
	for (int i=0;i<m;i++)
		pa[i]=(pairs*)malloc(n*sizeof(pairs));
	for (int i=0;i<m-1;i++)
		for (int j=0;j<n;j++)
			hi[i][j]=1;
	for (int i=0;i<m;i++)
		for (int j=0;j<n-1;j++)
			ve[i][j]=1;
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			pairs p;
			p.x=-1;
			p.y=-1;
			pa[i][j]=p;		
		}	
	}
	grid g;
	g.h=hi;
	g.v=ve;
	g.p=pa;
	return g;
}
void prnbhul (grid g,int m,int n)
{
	for (int i=0;i<n;i++)
		cout<<"+---";
	cout<<"+";
	cout<<endl;
	for (int i=0;i<m;i++)
	{
		cout<<"|   ";
		for (int j=0;j<n-1;j++)
		{
			if (g.v[i][j])
			{
				cout<<"|   ";
			}
			else
				cout<<"    ";
		}
		cout<<"|"<<endl;
		for (int j=0;j<n;j++)
		{
			if (i==m-1)
			{
				cout<<"+---";
			}
			else
			{
				if (g.h[i][j])
					cout<<"+---";
				else
					cout<<"+   ";
			}
		}
		cout<<"+";
		cout<<endl;
	}
}
void prnbhulfi (int** f,grid g,pairs king,pairs queen,int m,int n)
{
	for (int i=0;i<n;i++)
		cout<<"+---";
	cout<<"+";
	cout<<endl;
	for (int i=0;i<m;i++)
	{
		cout<<"|   ";
		for (int j=0;j<n-1;j++)
		{
			if (f[i][j]==0)
			{
			if (g.v[i][j])
			{
				cout<<"|   ";
			}
			else
				cout<<"    ";
			}
			else
			{
				pairs p;
				p.x=i;
				p.y=j;
				if (p.x==king.x&&p.y==king.y)
				{
					if (g.v[i][j])
			{
				cout<<"| S ";
			}
			else
				cout<<"  S ";
			}	
			else if (p.x==queen.x&&p.y==queen.y)
			{
				if (g.v[i][j])
			{
				cout<<"| T ";
			}
			else
				cout<<"  T ";
			}	
			else
			{
				if (g.v[i][j])
			{
				cout<<"| X ";
			}
			else
				cout<<"  X ";
			}
				}	
		}
		if (f[i][n-1])
		{
			cout<<"X";
		}
		cout<<"|"<<endl;
		for (int j=0;j<n;j++)
		{
			if (i==m-1)
			{
				cout<<"+---";
			}
			else
			{
				if (g.h[i][j])
					cout<<"+---";
				else
					cout<<"+   ";
			}
		}
		cout<<"+";
		cout<<endl;
	}
}
void dfs (grid* g, pairs st,int m,int n,int** vis)
{
	vis[st.x][st.y]=1;
	int temp=rand()%4;
	if (isvalid(st.x+1,st.y,m,n))
	{
		if (vis[st.x+1][st.y]==0)
		{
			g->h[st.x][st.y]=0;
			pairs p,p1;
			p.x=st.x;
			p.y=st.y;
			p1.x=st.x+1;
			p1.y=st.y;
			g->p[st.x+1][st.y]=p;
			dfs(g,p1,m,n,vis);
		}
	}
	if (isvalid(st.x,st.y+1,m,n))
	{
		if (vis[st.x][st.y+1]==0)
		{
			g->v[st.x][st.y]=0;
			pairs p,p1;
			p.x=st.x;
			p.y=st.y;
			p1.x=st.x;
			p1.y=st.y+1;
			g->p[st.x][st.y+1]=p;
			dfs(g,p1,m,n,vis);
		}
	}
	if (isvalid(st.x-1,st.y,m,n))
	{
		if (vis[st.x-1][st.y]==0)
		{
			g->h[st.x-1][st.y]=0;
			pairs p,p1;
			p.x=st.x;
			p.y=st.y;
			p1.x=st.x-1;
			p1.y=st.y;
			g->p[st.x-1][st.y]=p;
			dfs(g,p1,m,n,vis);
		}
	}
	if (isvalid(st.x,st.y-1,m,n))
	{
		if (vis[st.x][st.y-1]==0)
		{
			g->v[st.x][st.y-1]=0;
			pairs p,p1;
			p.x=st.x;
			p.y=st.y;
			p1.x=st.x;
			p1.y=st.y-1;
			g->p[st.x][st.y-1]=p;
			dfs(g,p1,m,n,vis);
		}
	}
}
grid genbhul (grid g,int m,int n)
{
	int stx=rand()%m;
	int sty=rand()%n;
	pairs start;
	start.x=stx;
	start.y=sty;
	int** vis;
	vis=(int**)malloc((m)*sizeof(int*));
	for (int i=0;i<m;i++)
		vis[i]=(int*)malloc(n*sizeof(int));
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			vis[i][j]=0;
		}
	}
	//cout<<start.x<<" "<<start.y<<endl;
	dfs(&g,start,m,n,vis);
	prnbhul(g,m,n);
	// for (int i=0;i<m;i++)
	// {
	// 	for (int j=0;j<n;j++)
	// 	{
	// 		cout<<g.p[i][j].x<<","<<g.p[i][j].y<<" ";
	// 	}
	// 	cout<<endl;
	// }
	return g;
}
int** findrani (pairs s,pairs t,grid g,int m,int n)
{
	int** vis1;
	int** vis2;
	int** fvis;
	//cout<<s.x<<" "<<s.y<<endl;
	vis1=(int**)malloc((m)*sizeof(int*));
	for (int i=0;i<m;i++)
		vis1[i]=(int*)malloc(n*sizeof(int));
	vis2=(int**)malloc((m)*sizeof(int*));
	for (int i=0;i<m;i++)
		vis2[i]=(int*)malloc(n*sizeof(int));
	fvis=(int**)malloc((m)*sizeof(int*));
	for (int i=0;i<m;i++)
		fvis[i]=(int*)malloc(n*sizeof(int));
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			vis1[i][j]=0;
			vis2[i][j]=0;
			fvis[i][j]=0;
		}
	}
	vis1[s.x][s.y]=1;
	pairs ps=g.p[s.x][s.y];
	pairs p;
	p.x=-1;
	p.y=-1;
	while (!((ps.x==p.x)&&(ps.y==p.y)))
	{
		vis1[ps.x][ps.y]=1;
		pairs par;
		par=g.p[ps.x][ps.y];
		ps=par;
	}
	vis2[t.x][t.y]=1;
	pairs pt=g.p[t.x][t.y];
	while (!((pt.x==p.x)&&(pt.y==p.y)))
	{
		vis2[pt.x][pt.y]=1;
		pairs par;
		par=g.p[pt.x][pt.y];
		pt=par;
	}
	pairs common;
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (vis1[i][j]==1&&vis2[i][j]==1)
			{
				common.x=i;
				common.y=j;
				break;
			}
		}
		//cout<<endl;
	}
	//cout<<common.x<<" "<<common.y<<endl;
	ps=g.p[s.x][s.y];
	pt=g.p[t.x][t.y];
	p.x=common.x;
	p.y=common.y;
	fvis[s.x][s.y]=1;
	fvis[t.x][t.y]=1;
	while (!((ps.x==p.x)&&(ps.y==p.y)))
	{
		fvis[ps.x][ps.y]=1;
		pairs par;
		par=g.p[ps.x][ps.y];
		ps=par;
	}
	while (!((pt.x==p.x)&&(pt.y==p.y)))
	{
		fvis[pt.x][pt.y]=1;
		pairs par;
		par=g.p[pt.x][pt.y];
		pt=par;
	}
	fvis[common.x][common.y]=1;

return fvis;
}
int main()
{
	srand((unsigned int)time(NULL));
	int m,n;
	cin>>m>>n;
	grid g;
	g=initbhul(m,n);
	cout<<"Initial "<<endl;
	prnbhul(g,m,n);
	cout<<"Random "<<endl;
	g=genbhul(g,m,n);
	int skx,sky,sqx,sqy;
	skx=rand()%4;
	sky=rand()%4;
	skx=rand()%4;
	sky=rand()%4;
	pairs king,queen;
	king.x=skx;
	king.y=sky;
	queen.x=skx;
	queen.y=sky;
	int** final;
	final=findrani(king,queen,g,m,n);
	cout<<"path "<<endl;
	prnbhulfi(final,g,king,queen,m,n);
}