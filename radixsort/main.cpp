#include <bits/stdc++.h>
using namespace std;

/// explanation here
/// http://rgrig.blogspot.ro/2008/08/sorting-out-stuff.html

ifstream f("radixsort.in");
ofstream g("radixsort.out");

const int nmax=10000005;
unsigned int A,B,C,N,v[nmax];

queue <unsigned int> buck[260]; /// o sa avem nevoie doar de 255 de buckets

int main()
{
    int i,j,k,l;
    f>>N>>A>>B>>C;

    v[1]=B;
    for (i=2;i<=N;i++)
     v[i]=(1LL*(1LL*A*v[i-1]+B))%C;

    for (i=1;i<=4;i++) /// parcurgem toti bytes unui numar (stiind ca are 32 de biti maxim , inseamna ca va avea maxim 4 bytes)
    {
        int shift=(i-1)*8;
        int destination=0; /// in care bucket trimitem numarul

        for (j=1;j<=N;j++)
        {
            destination=((v[j]>>shift)&255); /// shiftam cu un anumit numar de biti , astfel incat vom avea pe primii 8 biti byte-ul care ne intereseaza si scapam de bitii din fata
            buck[destination].push(v[j]);
        }

        k=0;

        for (j=0;j<=256;j++)
        {
            while (!buck[j].empty())
            {
                v[++k]=buck[j].front();
                buck[j].pop();
            }
        }
    }

    for (i=1;i<=N;i+=10)
     g<<v[i]<<" ";

    return 0;
}
