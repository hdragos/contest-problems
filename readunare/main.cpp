#include <bits/stdc++.h>
using namespace std;

ifstream f("readunare.in");
ofstream g("readunare.out");

const int nmax=10005;
char a[nmax];
string afis[nmax]; /// vector de stringuri , va fi mai usor pt concatenari (folosim + in loc de cat)
int val;

int main()
{
    int i,j;
    f>>a;
    i=0;
    while (a[i]=='{')
    {
        i++;
        val++;
    }

    f>>a;
    i=0;
    while (a[i]=='{')
    {
        i++;
        val++;
    }

    val-=2;

    afis[0]="{}";
    afis[1]="{{}}";
    for (i=2;i<=val;i++)
    {
        afis[i]+="{"; /// in cazul asta e concatenare
        for (j=i-1;j>=1;j--)
         afis[i]+= (afis[j]+","); /// concatenam multimile anterioare , cu virgula intre ele
        afis[i]+= afis[0];
        afis[i]+="}";
    }

    g<<afis[val];

    return 0;
}
