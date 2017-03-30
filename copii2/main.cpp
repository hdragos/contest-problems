#include <bits/stdc++.h>
using namespace std;

ifstream f("copii2.in");
ofstream g("copii2.out");

const int nmax=100005;
int bitk[nmax][35];
int logk[nmax];
vector <int> afis[nmax];

int n,k;

int descompose (int number , int ind)
{
    int j=0,rest;
    while (number)
    {
        rest=number%k;
        bitk[ind][++j]=rest;
        number/=k;
    }

}

void clean_stuff (int cleaner_size)
{
    int i;
    for (i=0;i<cleaner_size;i++)
        afis[i].clear();

}

int main()
{
    int i,j,m=0;
    f>>n>>k;

    for (i=1;i<=n;i++)
        descompose(i,i);

/*
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=logk[n]+1;j++)
         g<<bitk[i][j]<<" ";
        g<<'\n';
    }
*/

    long long t=1;

    while (t<n)
    {
        t*=k;
        m++;
    }

    g<<m<<'\n';

    int l,h,nrteams;
    for (j=1;j<=m;j++)
    {
        //g<<">"<<j<<'\n';
        nrteams=0;
        for (i=1;i<=n;i++)
        {
            if (afis[bitk[i][j]].empty())
                nrteams++;

            afis[bitk[i][j]].push_back(i);
        }

        g<<nrteams<<'\n';

        for (i=0;i<=k;i++)
        {
            if (!afis[i].empty())
            {
               l=afis[i].size();
               g<<l<<" ";
               for (h=0;h<l;h++)
                g<<afis[i][h]<<" ";

               g<<'\n';
            }
        }

        clean_stuff(n);

    }

    return 0;
}
