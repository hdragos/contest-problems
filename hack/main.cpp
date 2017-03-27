#include <bits/stdc++.h>
using namespace std;

ifstream f("hack.in");
ofstream g("hack.out");

/// din liniile umratoare
/// if(A[node.first][node.second] != A[newX][newY])
///   cost = 1;
/// deducem ca doar cand trecem de la 1 la 0 (sau invers se schimba costul , deci patratele de acelasi fel sunt parcurse pe "gratis")
/// de aici incercam sa "incapsulam" cat mai multe forme alcatuite doar din 1 , din cat mai multe directii


char A[55][55];

int main()
{
    int i,j;
    g<<"50 50 1 1"<<'\n';

    for (i=0;i<50;i++)
     for (j=0;j<50;j++)
      A[i][j]='0';

    for (i=0;i<50;i++)
    {
        if (i%2)
        {
            for (j=0;j<i-1;j++)
                A[i][j]=A[j][i]='1';
        }
    }

    for (i=0;i<50;i++)
    {
        for (j=0;j<50;j++)
         g<<A[i][j];
        g<<'\n';
    }

    return 0;
}
