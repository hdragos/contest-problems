#include <bits/stdc++.h>
using namespace std;
ifstream f("dragoni.in");
ofstream g("dragoni.out");

vector <int> drum[805];
vector <int> cost[805];
queue <int> cono;  // coada cu nodul actual
queue <int> codr;  // coada cu dragonul actual

int drake[805];
bool viz[805];
bool inq[805][805];
int n,m,i,tip,maxdrake,x,y,c,drummin=2000000000,j;
int mincost[805][805]; // drumul minim pana in nodul i cu dragonul j

int dfs (int nod)
{
    int h,l;
    l=drum[nod].size();
    if (viz[nod]==0)
    {
        viz[nod]=1;
        for (h=0;h<l;h++)
            if (viz[drum[nod][h]]==0)
             dfs(drum[nod][h]);
    }
}

void bellmanf ()
{
    int costac,drakeac,nodac,nodnou,drakenou,nrvecini,h,costnou,bestdrake;
    mincost[1][1]=0;
    inq[1][1]=1;
    cono.push(1);
    codr.push(1);
    while (!cono.empty())
    {
        nodac=cono.front();
        drakeac=codr.front();
        cono.pop();
        codr.pop();
        inq[nodac][drakeac]=0;
        nrvecini=drum[nodac].size();
        costac=mincost[nodac][drakeac];
        for (h=0;h<nrvecini;h++)
        {
            nodnou=drum[nodac][h];
            costnou=cost[nodac][h];
            if (costac+costnou<mincost[nodnou][drakeac] && drake[drakeac]>=costnou) // verificam daca putem merge cu dragonul actual la o insula invecinata
            {
                bestdrake=drakeac;
                if (drake[drum[nodac][h]]>drake[bestdrake]) // verificam care este cel mai bun dragon
                 bestdrake=drum[nodac][h];

                if (inq[nodnou][bestdrake]==0) // continuam cu cel mai bun dragon
                {
                    inq[nodnou][bestdrake]=1;
                    cono.push(nodnou);
                    codr.push(bestdrake);
                }
                mincost[nodnou][bestdrake]=costac+costnou;

                if (inq[nodnou][drakeac]==0) // continuam cu acelasi dragon
                {
                    inq[nodnou][drakeac]=1;
                    cono.push(nodnou);
                    codr.push(drakeac);
                  }
                mincost[nodnou][drakeac]=costac+costnou;
          }
    }
  }
}

int main()
{
   f>>tip;
   f>>n>>m;
   for (i=1;i<=n;i++)
       f>>drake[i];

   if (tip==1)
   {
       for (i=1;i<=m;i++)
       {
           f>>x>>y>>c;
           if (c<=drake[1])
           {
           drum[x].push_back(y);
           drum[y].push_back(x);
           }
       }
       dfs(1);
       for (i=1;i<=n;i++)
         if (viz[i])
           maxdrake=(maxdrake,drake[i]);
       g<<maxdrake;
       return 0;
   }

    for (i=1;i<=n;i++)
     for (j=1;j<=n;j++)
      mincost[i][j]=2000000000;

    for (i=1;i<=m;i++)
       {
           f>>x>>y>>c;
           drum[x].push_back(y);
           drum[y].push_back(x);
           cost[x].push_back(c);
           cost[y].push_back(c);
       }

    bellmanf();

    for (i=1;i<=n;i++)
        drummin=min(drummin,mincost[n][i]);

   g<<drummin;

   return 0;
}
