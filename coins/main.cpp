#include <bits/stdc++.h>
using namespace std;

ifstream f("coins.in");
ofstream g("coins.out");

const int LOGMAX = (1<<23);
int sum,n;
int memo[LOGMAX];

int winning_strat (int stare)
{
    if (memo[stare]!=-1) /// verificam daca avem deja calculat
     return memo[stare];

    if (((stare)&(stare+1))==0) /// verificam daca este strategie de castig
    {
        memo[stare]=1;
        return 1;
    }

    int k,zero_place=-1; /// zero_place este folosit pentru a vedea care este ultimul 0 liber
    for (k=0;k<22;k++)
    {
        if ((stare & (1<<k))==0)
         zero_place=k;
        else if (zero_place!=-1)
        {
            int aux=stare;
            ///schimbam bitii intre ei , adica mutam o moneda
            aux-=(1<<k);
            aux+=(1<<zero_place);
            if (winning_strat(aux)==0) /// in caz ca urmatoarea stare este una pierzatoare pentru oponent , inseamna ca starea actuala este castigatoare pentru noi
            {
                memo[stare]=1;
                return 1;
            }
        }
    }

    memo[stare]=0;
    return 0;

}

int main()
{
    f>>n;
    int aux,bit,mask,counter;

    memset(memo,-1,sizeof(memo)); /// initializam masca de stari cu -1, adica cu valoare necalculata

    while (n--)
    {
        mask=0; counter=0;
        for (int i=0;i<22;i++)
        {
            f>>bit;
            counter+=bit; /// adaugam banutul
            if (bit)
             mask|=(1<<i); /// construim masca
        }

       if (winning_strat(mask))
        sum+=counter;

    }

    g<<sum;

    return 0;
}
