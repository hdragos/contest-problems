#include <bits/stdc++.h>
using namespace std;

ifstream f("ratina.in");
ofstream g("ratina.out");

const int lunmax=2005;
const int nmax=10005;
const int logmax=25;
const int DIM=10005;

struct cuvant {char cuv[lunmax];int inipoz;};

cuvant a[nmax];
int n,m;
int acpoz[nmax]; /// acpoz[X.inipoz]= pozitia actuala in vectorul sortat a cuvantului X
int as_vec[nmax]; /// vector de asemanare intre 2 cuvinte consecutive , as_vec[i] = grad asemanare intre cuvantul i si i+1
int rmq[logmax][nmax]; /// pt minimul din as_vec
int loga[nmax];

int poz=0;
char buff[DIM];

void citeste(int &numar)
{
     numar = 0;
     while (buff[poz] < '0' || buff[poz] > '9')
          if (++poz == DIM)
               f.read(buff,DIM),poz=0;
     while ('0'<=buff[poz] && buff[poz]<='9')
     {
          numar = numar*10 + buff[poz] - '0';
          if (++poz == DIM)
               f.read(buff,DIM),poz=0;
     }
}

bool cmp(cuvant A , cuvant B)
{
    return strcmp(A.cuv,B.cuv)<0;
}

int asemanare (cuvant A , cuvant B)
{
    int i=0;
    while (A.cuv[i]==B.cuv[i] && A.cuv[i]!=NULL)
     i++;

    return i;
}

int query (int stanga, int dreapta)
{
    int ac_pow;
    ac_pow=loga[dreapta-stanga+1];
    return min(rmq[ac_pow][stanga],rmq[ac_pow][dreapta-(1<<ac_pow)+1]);
}

int main()
{
    int i,j,cuv_min,cuv_max,serie_actuala,aux,act_pow;
    f>>n>>m;

    f.get();

    loga[1]=0;
    for (i=2;i<=n+2;i++)
     loga[i]=loga[i/2]+1;

    for (i=1;i<=n;i++)
    {
        f>>a[i].cuv;
        a[i].inipoz=i;
    }

    sort(a+1,a+n+1,cmp);

    for (i=1;i<=n;i++)
        acpoz[a[i].inipoz]=i;

    for (i=1;i<n;i++)
    {
        as_vec[i]=asemanare(a[i],a[i+1]);
        rmq[0][i]=as_vec[i];
    }

    for(i=1;(1<<i)<=n;i++)
    {
       for(j=1;j+(1<<i)-1<=n;j++)
       {
          rmq[i][j]=min(rmq[i-1][j],rmq[i-1][j+(1<<(i-1))]);
       }
    }

    while (m--)
    {
        cuv_min=INT_MAX; /// primul cuvant din serie
        cuv_max=INT_MIN; /// ultimul cuvant din serie

        citeste(serie_actuala);

        for (j=1;j<=serie_actuala;j++)
        {
            citeste(aux);
            cuv_min=min(cuv_min,acpoz[aux]);
            cuv_max=max(cuv_max,acpoz[aux]);
        }

        if (cuv_max==cuv_min)
        {
            g<<strlen(a[cuv_min].cuv)<<'\n';
        }

        else
        {
            g<<query(cuv_min,cuv_max-1)<<'\n';
        }

    }

    return 0;
}
