#include <bits/stdc++.h>
#define step(x) (x & (-x))
using namespace std;

ifstream f("undo.in");
ofstream g("undo.out");

/// ideea problemei : vom rezolva query-urile offline , toata problema reducandu-se la o parcurge dfs a unui arbore creat de noi
/// operatiile de tip 1 adauga un nou nod in arbore (muchiile fiind de forma <pair <int,muchie> > , unde primul membru reprezinta
/// nodul in care suntem trimisi , iar structul "muchie" reprezinta un update (x,y,valoare). Operatiile de tipul 1 genereaza tot timpul
/// noduri noi. Operatiile de tip 3 ne intorc la stari anterioare , deci implicit la noduri anterioare. Ca sa ne dam seama la ce stari
/// anterioare am fost , vom folosi un vector care retine toate starile (in cazul nostru vec_nodes). Query-urile sunt retinute in noduri
/// si sunt rezolvate in parcurgerea dfs. Cand citim o operatie de tipul 2 vedem care este nodul actual (luat din vec_nodes) si adaugam in
/// acel nod (prin intermediul vectorului queries) o interogare care va fi rezolvata in timpul dfs-ului. In timpul dfs-ului interogarile
/// nu vor fi rezolvate neaparat in ordine , de aceea pentru structul "interogare" vom retine indicele initial al interogarii , pe care
/// il vom folosi sa punem raspunsurile la fiecare interogare in locul lor corespunzator in vectorul ordered_queries , in care se afla
/// raspunsurile finale.

struct muchie {int X,Y,valoare;};
struct interogare {int X,Y,poz_ini;};
int n,T;
const int nmax=500005;
int aib[525][525];
vector <pair <int,muchie> > graf[nmax];
vector <interogare> queries[nmax];
int vec_nodes[nmax];
int ordered_queries[nmax];

void update (int X,int Y,int val)
{
    int i,j;
    for (i=X;i<=n;i+=step(i))
     for (j=Y;j<=n;j+=step(j))
      aib[i][j]+= val;
}

int query (int X , int Y )
{
    int i,j,sum=0;
    for (i=X;i>=1;i-=step(i))
     for (j=Y;j>=1;j-=step(j))
      sum+=aib[i][j];

    return sum;
}

void dfs (int nod)
{
    int vecini,h,queries_in_node;
    vecini=graf[nod].size();
    queries_in_node=queries[nod].size();

    for (h=0;h<queries_in_node;h++) /// solve queries in node
    {
        ordered_queries[queries[nod][h].poz_ini]=query(queries[nod][h].X,queries[nod][h].Y);
    }

    for (h=0;h<vecini;h++) /// go to next nodes
    {
        update(graf[nod][h].second.X,graf[nod][h].second.Y,graf[nod][h].second.valoare);
        dfs(graf[nod][h].first);
        update(graf[nod][h].second.X,graf[nod][h].second.Y,-graf[nod][h].second.valoare);
    }

}

int main()
{
    f>>n>>T;

    int i,tip,nr_interogare=0,node=0,ind_ac=0,ac_node,steps_back;
    muchie ac_muc;
    interogare ac_int;

    for (i=1;i<=T;i++)
    {
        f>>tip;
        if (tip==1)
        {
           f>>ac_muc.X>>ac_muc.Y>>ac_muc.valoare;
           ac_node=vec_nodes[ind_ac];
           graf[ac_node].push_back(make_pair(++node,ac_muc));
           vec_nodes[ind_ac+1]=node;
           ind_ac++;
        }

        if (tip==2)
        {
            f>>ac_int.X>>ac_int.Y;
            ac_int.poz_ini=++nr_interogare;
            ac_node=vec_nodes[ind_ac];
            queries[ac_node].push_back(ac_int);
        }

        if (tip==3)
        {
            f>>steps_back;
            vec_nodes[ind_ac+1]=vec_nodes[ind_ac-steps_back];
            ind_ac++;
        }
    }

    dfs(0);

    for (i=1;i<=nr_interogare;i++)
     g<<ordered_queries[i]<<'\n';

    return 0;
}
