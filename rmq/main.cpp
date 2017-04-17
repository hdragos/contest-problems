#include <bits/stdc++.h>
using namespace std;
/// rmq[i][j] = minimul din intervalul ( j , j+2^i-1 )
ifstream f("rmq.in");
ofstream g("rmq.out");
const int nmax=100005;
const int log_nmax=18;
int a[nmax],rmq[log_nmax][nmax],loga[nmax],i,j,n,m,st,dr;

int query (int x,int y)
{
    int l;
    l=loga[y-x+1];
    return min(rmq[l][x],rmq[l][y-(1<<l)+1]);
}

int main()
{
    f>>n>>m;
    for (i=1;i<=n;i++)
    {
        f>>a[i];
        rmq[0][i]=a[i];
    }

    for (i=2;i<=n;i++)
        loga[i]=loga[i/2]+1;

    for (i=1;(1<<i)<=n;i++)
    {
        for (j=1;j+(1<<i)-1<=n;j++)
        {
            rmq[i][j]=min(rmq[i-1][j],rmq[i-1][j+(1<<(i-1))]);
        }
    }

    for (i=1;i<=m;i++)
    {
        f>>st>>dr;
        g<<query(st,dr)<<'\n';
    }

    return 0;
}
