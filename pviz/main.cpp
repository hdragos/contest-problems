#include <bits/stdc++.h>
using namespace std;

ifstream f("pviz.in");
ofstream g("pviz.out");

const int nmax=2005;
const int modulo=10007;
int d[nmax]; /// d[i] = al i-lea termen din vectorul initial de numere vizibile
int a[3][nmax]; /// a[i][j] = = numărul permutărilor de lungime i care conţin primele j elemente vizibile. (redusa la 2 linii)
int n,m;

int main()
{
    int i,j,actual_line;
    f>>n>>m;
    for (i=1;i<=m;i++)
        f>>d[i];

    a[1][1]=1;
    for (i=1;i<=n;i++)
     for (j=1;j<=m;j++)
     {
         actual_line=i%2; /// acelasi lucru cu i&1

         if (i==1 && j==1)
          continue;
         else
          a[actual_line][j] = (a[1-actual_line][j-1] + (d[j]-(i-1))*a[1-actual_line][j])%modulo; /// 1-actual_line e pentru a lua cealalta linie (1-0=1 , 1-1=0)
     }


      /// a[i-1][j-1] reprezintă cazul în care pe poziţia i se pune cel de-al j-lea element vizibil
      /// Al doilea termen reprezintă faptul că pe poziţia i se plasează un element ce nu este vizibil,
      /// acesta putând fi ales din numerele mai mici decât d[j], care nu au fost puse încă în permutare (de aici d[j]-(i-1))

   g<<a[n%2][m];

    return 0;
}
