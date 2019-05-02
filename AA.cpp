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
struct edge 
{
	pairs a,b;
	int weight;
};
typedef struct tree tree;
typedef struct edge edge;
typedef struct grid grid;
struct ret
{
	grid gi;
	pairs** par;
};
typedef struct ret ret;
bool isvalid (int i,int j,int m,int n)
{
	if (i>=0&&i<m&&j>=0&&j<n)
		return true;
	else
		return false;
}
pairs root(pairs** Arr,pairs t)
{
    while(1)          
    {
    	if (Arr[t.x][t.y].x==t.x&&Arr[t.x][t.y].y==t.y)
    		break;
    	t=Arr[t.x][t.y];
    }
    return t;
}
void weighteduni(pairs** Arr,int** size, pairs A,pairs B)
{
    pairs root_A = root(Arr,A);
    pairs root_B = root(Arr,B);
    if(size[root_A.x][root_A.y] < size[root_B.x][root_B.y])
    {
	Arr[root_A.x][root_A.y]= Arr[root_B.x][root_B.y];
	size[root_B.x][root_B.y] += size[root_A.x][root_A.y];
}
    else
    {
Arr[root_B.x][root_B.y] = Arr[root_A.x][root_A.y];
size[root_A.x][root_A.y] += size[root_B.x][root_B.y];
}
}
bool find(pairs** Arr,pairs A,pairs B)
{
    if(root(Arr,A).x==root(Arr,B).x&&root(Arr,A).y==root(Arr,B).y)      
    return true;
    else
    return false;
}
int partition (edge* a, int low, int high)
{
	int i=low;
	int j=low;
	int k=high;
	int p=a[low].weight;
	while (j<=k)
	{
		if (a[j].weight==p)
			j++;
		else if (a[j].weight<p)
		{
			edge t=a[i];
			a[i]=a[j];
			a[j]=t;
			i++;
			j++;
		}
		else
		{
			edge t=a[k];
			a[k]=a[j];
			a[j]=t;
			k--;
		}
	}
	return i;
}
void quick_sort (edge* a,int low,int high)
{
	if (low<high)
	{
		int p=partition(a,low,high);
		quick_sort(a,low,p-1);
		quick_sort(a,p+1,high);
	}
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
ret MSTbhul (grid g,edge* edges,int z,int m,int n)
{
	pairs** arr;
	pairs** par;
	par=(pairs**)malloc(m*sizeof(pairs*));
	for (int i=0;i<m;i++)
		par[i]=(pairs*)malloc(n*sizeof(pairs));
	arr=(pairs**)malloc(m*sizeof(pairs*));
	for (int i=0;i<m;i++)
		arr[i]=(pairs*)malloc(n*sizeof(pairs));
	int** size;
	size=(int**)malloc(m*sizeof(int*));
	for (int i=0;i<m;i++)
		size[i]=(int*)malloc(n*sizeof(int));
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			arr[i][j].x=i;
			arr[i][j].y=j;
			size[i][j]=1;
			par[i][j].x=i;
			par[i][j].y=j;
		}
	}
	for (int i=0;i<z;i++)
	{
		if (find(arr,edges[i].a,edges[i].b))
			continue;
		else
		{
			weighteduni(arr,size,edges[i].a,edges[i].b);
			if (edges[i].a.x==edges[i].b.x+1&&edges[i].a.y==edges[i].b.y)
			{
				g.h[edges[i].b.x][edges[i].b.y]=0;
				par[edges[i].a.x][edges[i].a.y]=par[edges[i].b.x][edges[i].b.y];
			}
			else if (edges[i].a.x+1==edges[i].b.x&&edges[i].a.y==edges[i].b.y)
			{
				g.h[edges[i].a.x][edges[i].a.y]=0;
				par[edges[i].b.x][edges[i].b.y]=par[edges[i].a.x][edges[i].a.y];
			}
			else if (edges[i].a.x==edges[i].b.x&&edges[i].a.y+1==edges[i].b.y)
			{
				g.v[edges[i].a.x][edges[i].a.y]=0;
				par[edges[i].b.x][edges[i].b.y]=par[edges[i].a.x][edges[i].a.y];
			}
			else if (edges[i].a.x==edges[i].b.x&&edges[i].a.y==edges[i].b.y+1)
			{
				g.v[edges[i].b.x][edges[i].b.y]=0;
				par[edges[i].a.x][edges[i].a.y]=par[edges[i].b.x][edges[i].b.y];
			}
		}
	}
	ret temp;
	temp.gi=g;
	temp.par=arr;
	return temp;
}
void prnbhulfi(grid b,int** vis,int m,int n){
 
 for(int i=0;i<=m;i++){ 
  
   if(i==0){
   for(int j=0;j<n;j++){
          cout<<"+---";
   }
   cout<<"+"<<endl;
   }
   else{
    

     for(int j=0;j<=n;j++){
       
        if(j==0){

            cout<<"|";
        }
        else{
          if(vis[i-1][j-1]==1){
              cout<<" X";

          }
          else if (vis[i-1][j-1]==2)
          	cout<<" S";
          else if (vis[i-1][j-1]==3)
          	cout<<" T";
          if(!vis[i-1][j-1])
              cout<<"  ";

         if(b.v[i-1][j-1]==1){
             cout<<" |";
         }
         if(!b.v[i-1][j-1])
             cout<<"  ";
        }
     }
     cout<<"|"<<endl;
     if(i<m){
          for(int j=0;j<n;j++){

          if(b.h[i-1][j])
             cout<<"+---";
            else
            cout<<"+   ";
           
     }
         cout<<"+"<<endl;
      }
      if(i==m){
   for(int j=0;j<n;j++){
          cout<<"+---";
   }
   cout<<"+"<<endl;

   }

 }



}

}
int** findrani (grid g,pairs** arr,int m,int n)
{
	pairs king,queen;
	pairs** par;
	par=(pairs**)malloc(m*sizeof(pairs*));
	for (int i=0;i<m;i++)
		par[i]=(pairs*)malloc(n*sizeof(pairs));
	king.x=rand()%m;
	king.y=rand()%n;
	queen.x=rand()%m;
	queen.y=rand()%n;
	cout<<endl;
	cout<<"Path from ("<<king.x<<","<<king.y<<") to ("<<queen.x<<" "<<queen.y<<")"<<endl;
	int** vis;
	int** vis1;
	vis=(int**)malloc((m)*sizeof(int*));
	for (int i=0;i<m;i++)
		vis[i]=(int*)malloc(n*sizeof(int));
	vis1=(int**)malloc((m)*sizeof(int*));
	for (int i=0;i<m;i++)
		vis1[i]=(int*)malloc(n*sizeof(int));
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			vis[i][j]=0;
			vis1[i][j]=0;
		}
	}
	queue <pairs> q;
	q.push(king);
	vis[king.x][king.y]=2;
	//vis[queen.x][queen.y]=2;
	par[king.x][king.y].x=-1;
	par[king.x][king.y].y=-1;
	pairs tk,tq;
	tk=king;
	tq=queen;
	while (!q.empty())
	{
		pairs p;
		p=q.front();
		q.pop();
		if (vis[queen.x][queen.y])
		{
			vis[queen.x][queen.y]=3;
			break;
		}
		else
		{
			pairs ri,le,to,bo;
			ri.x=p.x;
			ri.y=p.y+1;
			le.x=p.x;
			le.y=p.y-1;
			to.x=p.x-1;
			to.y=p.y;
			bo.x=p.x+1;
			bo.y=p.y;
			if (isvalid(ri.x,ri.y,m,n))
			{
				if (vis[ri.x][ri.y]==0)
				{
					if (g.v[p.x][p.y]==0)
					{
					vis[ri.x][ri.y]=1;
					par[ri.x][ri.y]=p;
					q.push(ri);
					}
				}
			}
			if (isvalid(le.x,le.y,m,n))
			{
				if (vis[le.x][le.y]==0)
				{
					if (g.v[le.x][le.y]==0)
					{
					vis[le.x][le.y]=1;
					q.push(le);
					par[le.x][le.y]=p;
					}
				}
			}
			if (isvalid(bo.x,bo.y,m,n))
			{
				if (vis[bo.x][bo.y]==0)
				{
					if (g.h[p.x][p.y]==0)
					{
					vis[bo.x][bo.y]=1;
					q.push(bo);
					par[bo.x][bo.y]=p;
					}
				}
			}
			if (isvalid(to.x,to.y,m,n))
			{
				if (vis[to.x][to.y]==0)
				{
					if (g.h[to.x][to.y]==0)
					{
					vis[to.x][to.y]=1;
					q.push(to);
					par[to.x][to.y]=p;
					}
				}
			}
		}
	}
	pairs qu=queen;
	while (1)
	{
		if (par[qu.x][qu.y].x==-1&&par[qu.x][qu.y].y==-1)
		{
			vis1[qu.x][qu.y]=2;
			break;
		}
		else
		{
			vis1[qu.x][qu.y]=1;
			qu=par[qu.x][qu.y];
		}
	}
	vis1[queen.x][queen.y]=3;
	return vis1;
	}
int main()
{
	srand((unsigned int)time(NULL));
	int m,n;
	cin>>m>>n;
	grid g;
	g=initbhul(m,n);
	cout<<"Initial BhulBhulaiya"<<endl;
	prnbhul(g,m,n);
	edge* edges;
	edges=(edge*)malloc(4*m*n*sizeof(edge));
	int z=0;
	for (int i=0;i<m-1;i++)
	{
		for (int j=0;j<n;j++)
		{
				edges[z].a.x=i;
				edges[z].a.y=j;
				edges[z].b.x=i+1;
				edges[z].b.y=j;
				edges[z].weight=rand()%1000+1;
				z++;
		}
	}
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n-1;j++)
		{
				edges[z].a.x=i;
				edges[z].a.y=j;
				edges[z].b.x=i;
				edges[z].b.y=j+1;
				edges[z].weight=rand()%1000+1;
				z++;
		}
	}
	quick_sort(edges,0,z-1);
	//grid gmst;
	ret temp;
	temp=MSTbhul(g,edges,z,m,n);
	cout<<"Randomised BhulBhulaiya";
	cout<<endl;
	prnbhul(temp.gi,m,n);
	int** vis;
	vis=findrani(temp.gi,temp.par,m,n);
	// for (int i=0;i<m;i++)
	// {
	// 	for (int j=0;j<n;j++)
	// 	{
	// 		cout<<vis[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	cout<<endl;
	prnbhulfi(temp.gi,vis,m,n);
}	