#include <bits/stdc++.h>
using namespace std;
ifstream f("ct.in");
ofstream g("ct.out");
const int nmax=100005;
int euler[2*nmax],loga[2*nmax],first[nmax],n,k,t,i,x,y,nivel[nmax],cnt,j;
vector <int> a[nmax];
int rmq[21][2*nmax],nmin[21][2*nmax];
int viz[nmax],csiz;
struct lcav {int lca,x,y;};
lcav cod[nmax];

void mark (int nod)
{
    int h,vecini;
    viz[nod]=-1;
    vecini=a[nod].size();
    for (h=0;h<vecini;h++)
    {
        if (viz[a[nod][h]]!=-1 && nivel[a[nod][h]]==nivel[nod]+1)
         mark(a[nod][h]);
    }
}

bool cmp (lcav A , lcav B)
{
    return nivel[A.lca]>nivel[B.lca];
}

void clean (int siz)
{
    int h;
    for (h=1;h<=siz;h++)
    {
        a[h].clear();
        viz[h]=0;
        nivel[h]=0;
    }
}

void parcurgere (int nod)
{
    int vecini,h;
    viz[nod]=1;
    euler[++cnt]=nod;
    first[nod]=cnt;
    vecini=a[nod].size();
    for (h=0;h<vecini;h++)
    {
        if (viz[a[nod][h]]==0)
        {
            nivel[a[nod][h]]=nivel[nod]+1;
            parcurgere(a[nod][h]);
            euler[++cnt]=nod;
        }

    }
}

int LCA (int A,int B)
{
    int X,Y,lun;
    X=first[A];
    Y=first[B];
    if (X>Y) swap(X,Y);
    lun=Y-X+1;
    lun=loga[lun];
    if (rmq[lun][X]<rmq[lun][Y-(1<<lun)+1])
     return nmin[lun][X];
    return nmin[lun][Y-(1<<lun)+1];
}

void bomb()
{
    int h,ras=0;
    for (h=1;h<=k;h++)
    {
        if (viz[cod[h].x]!=-1 && viz[cod[h].y]!=-1)
        {
            ras++;
            mark(cod[h].lca);
        }
    }
    g<<ras<<'\n';
}

int main()
{
    f>>t;
    while (t--)
    {
        cnt=0;
        f>>n>>k;
        for (i=1;i<=n-1;i++)
        {
            f>>x>>y;
            a[x].push_back(y);
            a[y].push_back(x);
        }

        parcurgere(1);
/*
        for (i=1;i<=cnt;i++)
         g<<euler[i]<<" ";
        g<<'\n';
        for (i=1;i<=cnt;i++)
         g<<nivel[euler[i]]<<" ";
        g<<'\n';
        g<<'\n';
*/

        for (i=2;i<=cnt;i++)
         loga[i]=loga[i/2]+1;

        for (i=1;i<=cnt;i++)
        {
            rmq[0][i]=nivel[euler[i]];
            nmin[0][i]=euler[i];
        }

        for (i=1;(1<<i)<=cnt;i++)
         for (j=1;j+(1<<i)-1<=cnt;j++)
         {
             if (rmq[i-1][j]<rmq[i-1][j+(1<<(i-1))])
             {
                 rmq[i][j]=rmq[i-1][j];
                 nmin[i][j]=nmin[i-1][j];
             }
             else
             {
                 rmq[i][j]=rmq[i-1][j+(1<<(i-1))];
                 nmin[i][j]=nmin[i-1][j+(1<<(i-1))];
             }
         }

         for (i=1;i<=k;i++)
         {
             f>>x>>y;
             cod[i].x=x;
             cod[i].y=y;
             cod[i].lca=LCA(x,y);
         }

         sort(cod+1,cod+1+k,cmp);

         bomb();
         clean(n);

    }
    return 0;
}
