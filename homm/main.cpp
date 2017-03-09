#include <fstream>
#define Nmax 105
#define Kmax 25
using namespace std;

ifstream f("homm.in"); // homm2 , muh childhood
ofstream g("homm.out");

int a[Nmax][Nmax][Kmax];
int harta[Nmax][Nmax];
int h,i,j,k,n,m,xi,yi,xf,yf,sum;

int main()
{
    f>>n>>m>>k;
    for (i=1;i<=n;i++)
     for (j=1;j<=m;j++)
      f>>harta[i][j];
    for (i=0;i<=n+1;i++)
     {harta[i][m+1]=1;
      harta[i][0]=1;
     }
    for (j=0;j<=m+1;j++)
     {harta[n+1][j]=1;
      harta[0][j]=1;
     }

    f>>xi>>yi>>xf>>yf;
    if (harta[xi][yi] || harta[xf][yf])
     g<<0;
    else
    {
        if (!harta[xi-1][yi]) a[xi-1][yi][1]=1;
        if (!harta[xi+1][yi]) a[xi+1][yi][1]=1;
        if (!harta[xi][yi-1]) a[xi][yi-1][1]=1;
        if (!harta[xi][yi+1]) a[xi][yi+1][1]=1;
        for (h=2;h<=k;h++)
         for (i=1;i<=n;i++)
          for (j=1;j<=m;j++)
           if (!harta[i][j])
            a[i][j][h]+=a[i-1][j][h-1]+a[i+1][j][h-1]+a[i][j+1][h-1]+a[i][j-1][h-1];
        for (h=1;h<=k;h++)
         sum+=a[xf][yf][h];
        if (xi==xf && yi==yf)
         g<<sum+1;
        else
         g<<sum;
    }

    return 0;
}
