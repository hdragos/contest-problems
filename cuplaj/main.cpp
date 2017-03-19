#include <bits/stdc++.h>
using namespace std;

ifstream f("cuplaj.in");
ofstream g("cuplaj.out");

const int nmax=20005;
vector <int> graf[nmax];
int vizitat[nmax];
int dreapta[nmax]; /// dreapta[i] = nodul din multimea dreapta (a 2-a) cu care este cuplat nodul i;
int stanga[nmax]; /// stanga[i] = nodul din multimea stanga (prima) cu care este cuplat nodul i;
int n,m,e,sol;

int cupleaza (int nod) /// cuplam cat putem incepand din nodul "nod" (greedy) , 1 cand am cuplat ceva , 0 cand nu am cuplat nimic
{
    int i,nod_nou,vecini;
    if (vizitat[nod]==1)
     return 0;

    vizitat[nod]=1;

    vecini=graf[nod].size();
    for (i=0;i<vecini;i++)
    {
        nod_nou=graf[nod][i];
        if (stanga[nod_nou]==0 || cupleaza(stanga[nod_nou])) /// chestia asta ne va duce recursiv prin tot graful , cupland cat de mult putem
        {
            dreapta[nod]=nod_nou;
            stanga[nod_nou]=nod;
            return 1;
        }
    }

    return 0;
}

void solve ()
{
    int i,nr_cuplaje=1;
    while (nr_cuplaje>0) /// cuplam pana nu mai putem cupla (greedy)
    {
        nr_cuplaje=0;
        memset(vizitat,0,sizeof(vizitat));
        for (i=1;i<=n;i++) /// incercam sa cuplam nodurile din partea stanga cu cele din partea dreapta
        {
            if (dreapta[i]==0)
             if (cupleaza(i)) nr_cuplaje++;
        }
    }
}

int main()
{
    int i,x,y;
    f>>n>>m>>e;
    for (i=1;i<=e;i++)
    {
        f>>x>>y;
        graf[x].push_back(y+n);
        graf[y+n].push_back(x);
    }

    solve();

    for (i=1;i<=n;i++)
     if (dreapta[i])
      sol++;

    g<<sol<<'\n';

    for (i=1;i<=n;i++)
     if (dreapta[i])
      g<<i<<" "<<dreapta[i]-n<<'\n';

    return 0;
}
