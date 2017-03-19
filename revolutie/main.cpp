#include <bits/stdc++.h>
using namespace std;

ifstream f("revolutie.in");
ofstream g("revolutie.out");

const int nmax=270;
vector <int> graf[nmax];
vector <pair <int,int> > mutari;
int stanga[nmax];
int dreapta[nmax];
int vizitat[nmax];
int n;

int cupleaza (int nod)
{
    int vecini,nod_nou,i;
    if (vizitat[nod]==1)
     return 0;
    vizitat[nod]=1;

    vecini=graf[nod].size();
    for (i=0;i<vecini;i++)
    {
        nod_nou=graf[nod][i];
        if (stanga[nod_nou]==0 || cupleaza(stanga[nod_nou]))
        {
            dreapta[nod]=nod_nou;
            stanga[nod_nou]=nod;
            return 1;
        }
    }

    return 0;
}

void realizeaza_cuplaje()
{
    int nr_cuplaje=1,i;

    while (nr_cuplaje>0)
    {
        nr_cuplaje=0;
        memset(vizitat,0,sizeof(vizitat));
        for (i=1;i<=n;i++)
        {
            if (dreapta[i]==0)
             if (cupleaza(i)) nr_cuplaje++;
        }
    }
}

void afisare ()
{
    int i,aux1,aux2;
    for (i=1;i<=n;i++)
    {
        if (dreapta[i]!=n+i)
        {
            /// daca nodul i nu este conectac corespunzator nodului din dreapta (adica nu avem 1 pe punctul (i,i))
            /// vedem cine este conectac cu nodul i si ii interschimbam
            aux1=dreapta[i];
            aux2=stanga[n+i];

            mutari.push_back(make_pair(i,aux2));

            dreapta[aux2]=aux1;
            stanga[aux1]=aux2;

            dreapta[i]=n+i;
            stanga[n+i]=i;
        }
    }

    int afis_siz=mutari.size();
    g<<afis_siz<<'\n';

    for (i=0;i<afis_siz;i++)
     g<<"L "<<mutari[i].first<<" "<<mutari[i].second<<'\n';
}

int main()
{
    int i,j,x,elemente_cuplate=0;
    f>>n;
    for (i=1;i<=n;i++)
     for (j=1;j<=n;j++)
      {
          f>>x;
          if (x==1)
          {
              graf[i].push_back(j+n);
              graf[j+n].push_back(i);
          }
      }

    realizeaza_cuplaje();

    for (i=1;i<=n;i++)
     if (dreapta[i])
      elemente_cuplate++;

    if (elemente_cuplate<n)
    {
        g<<"-1";
        return 0;
    }

    afisare();

    return 0;
}
