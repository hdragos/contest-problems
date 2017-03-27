#include <bits/stdc++.h>
using namespace std;

ifstream f("senat.in");
ofstream g("senat.out");

const int nmax=255;
const int ct_buff_size=1005;
vector <int> graf[nmax];
int n,m;
char buff[ct_buff_size];
int stanga[nmax];
int dreapta[nmax];
int vizitat[nmax];

int match (int nod)
{
    int vecini,nod_nou,i;
    if (vizitat[nod]==1)
        return 0;
    vizitat[nod]=1;

    vecini=graf[nod].size();
    for (i=0;i<vecini;i++)
    {
        nod_nou=graf[nod][i];
        if (stanga[nod_nou]==0 || match(stanga[nod_nou])==1)
        {
            stanga[nod_nou]=nod;
            dreapta[nod]=nod_nou;
            return 1;
        }
    }

    return 0;
}

void make_matches()
{
    int number_of_matches,i;
    number_of_matches=1;

    while (number_of_matches>0)
    {
        number_of_matches=0;
        memset(vizitat,0,sizeof(vizitat));
        for (i=1;i<=m;i++)
        {
            if (dreapta[i]==0)
                if (match(i))
                 number_of_matches++;
        }
    }

}

int main()
{
    int i,j,l,numar;
    f>>n;
    f.get();
    f>>m;
    f.get();

    for (i=1;i<=m;i++)
    {
        f.getline(buff,ct_buff_size);
        l=strlen(buff);
        numar=0;
        for (j=0;j<=l;j++)
        {
           if (buff[j]<'0' || buff[j]>'9')
           {
               if (numar>0)
                   graf[i].push_back(numar+m);
               numar=0;
           }

           if (buff[j]>='0' && buff[j]<='9')
             numar=numar*10+(buff[j]-'0');
        }

        if (numar>0)
            graf[i].push_back(numar+m);

    }

    make_matches();

    int matched_rooms=0;
    for (i=1;i<=m;i++)
        if (dreapta[i])
         matched_rooms++;

    if (matched_rooms!=m)
    {
        g<<"0";
        return 0;
    }

    for (i=1;i<=m;i++)
        g<<dreapta[i]-m<<'\n';

    return 0;
}
