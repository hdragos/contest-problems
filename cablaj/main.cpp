#include <bits/stdc++.h>
using namespace std;
ifstream f("cablaj.in");
ofstream g("cablaj.out");
const int nmax=3005;
int n;
double cost_total,cmin[nmax]; /// cmin[i]=distanta minima de la arborele nostru pana la punctul i , daca cmin[i]=-1 , inseamna ca i este in arbore
struct punct {double x,y;};
punct a[nmax];

double distanta (punct A , punct B)
{
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

void prim ()
{
    int i;
    int siz_arb=n-1,nod=1,nod_ac;
    double cost_minim,dist_aux;
    cmin[nod]=-1; /// introducem nodul 1 in arbore (pentru ca "bagam" suna prea taranesc)
    for (i=2;i<=n;i++)
     cmin[i]=distanta(a[nod],a[i]);
    while (siz_arb)
    {
      cost_minim=INT_MAX;
      for (i=2;i<=n;i++)
        if (cmin[i]>0 && cmin[i]<cost_minim) /// cautam cel mai apropiat punct de arborele nostru
         {
             nod_ac=i;
             cost_minim=cmin[i];
         }
      cmin[nod_ac]=-1; /// introducm nodul cel mai apropiat in arbore
      if (cost_minim!=INT_MAX)
       cost_total+=cost_minim;
      for (i=2;i<=n;i++) /// actualizam distantele
      {
          dist_aux=distanta(a[nod_ac],a[i]);
          if (cmin[i]>dist_aux)
           cmin[i]=dist_aux;
      }
      siz_arb--;
    }
}

int main()
{
    int i;
    f>>n;
    for (i=1;i<=n;i++)
     f>>a[i].x>>a[i].y;

    prim();
    g<<fixed<<setprecision(5);
    g<<cost_total;

    return 0;
}
