#include <bits/stdc++.h>
using namespace std;
ifstream f("plantatie.in");
ofstream g("plantatie.out");
int n,m,i,j,k,xini,yini,lungime;
int rmq[20][505][505],loga[505];

int query (int x, int y,int lat)
{
    int l,t1,t2,t3,t4;
    l=loga[lat];
    lat--;
    t1=rmq[l][x][y];
    t2=rmq[l][x+lat-(1<<l)+1][y];
    t3=rmq[l][x][y+lat-(1<<l)+1];
    t4=rmq[l][x+lat-(1<<l)+1][y+lat-(1<<l)+1];
    return max(max(t1,t2),max(t3,t4));
}

int main()
{
    f>>n>>m;
    for (i=1;i<=n;i++)
     for (j=1;j<=n;j++)
          f>>rmq[0][i][j];


    for (i=2;i<=n;i++)
     loga[i]=loga[i/2]+1;

    for (k=1;(1<<k)<=n;k++)
        for (i=1;i+(1<<k)-1<=n;i++)
         for (j=1;j+(1<<k)-1<=n;j++)
             rmq[k][i][j]=max(max(rmq[k-1][i][j],rmq[k-1][i+(1<<(k-1))][j]),max(rmq[k-1][i][j+(1<<(k-1))],rmq[k-1][i+(1<<(k-1))][j+(1<<(k-1))]));

    for (i=1;i<=m;i++)
    {
        f>>xini>>yini>>lungime;
        g<<query(xini,yini,lungime)<<'\n';
    }

    return 0;
}
