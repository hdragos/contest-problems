#include <bits/stdc++.h>
using namespace std;

ifstream f("drum2.in");
ofstream g("drum2.out");

const int nmax=32;
int a[nmax][nmax][nmax],n;
int dp[nmax][nmax][nmax],nr_ord;

void afisare (int x,int y,int z)
{
    if (z>n)
        return;
    g<<a[x][y][z]<<" ";

    int maxim=INT_MIN,x_plus=0,y_plus=0;
    if (dp[x][y+1][z+1]>maxim)
    {
        maxim=dp[x][y+1][z+1];
        y_plus=1;
        x_plus=0;
    }

    if (dp[x+1][y][z+1]>maxim)
    {
        maxim=dp[x+1][y][z+1];
        x_plus=1;
        y_plus=0;
    }

    if (dp[x+1][y+1][z+1]>maxim)
    {
        maxim=dp[x+1][y+1][z+1];
        x_plus=1;
        y_plus=1;
    }

    afisare(x+x_plus,y+y_plus,z+1);
}

int main()
{
    int i,j,k;
    f>>n;
    for (k=1;k<=n;k++)
        for (i=1;i<=k;i++)
            for (j=1;j<=k;j++)
                 f>>a[i][j][k];
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            dp[i][j][n]=a[i][j][n];

    for (k=n;k>=2;k--)
     for (i=k;i>=1;i--)
       for (j=k;j>=1;j--)
       {
           dp[i-1][j-1][k-1]=max(dp[i-1][j-1][k-1],dp[i][j][k]+a[i-1][j-1][k-1]);
           dp[i][j-1][k-1]=max(dp[i][j-1][k-1],dp[i][j][k]+a[i][j-1][k-1]);
           dp[i-1][j][k-1]=max(dp[i-1][j][k-1],dp[i][j][k]+a[i-1][j][k-1]);
       }

    g<<dp[1][1][1]<<'\n';

    for (k=1;k<=n;k++)
        for (i=1;i<=k;i++)
            for (j=1;j<=k;j++)
                 a[i][j][k]=++nr_ord;

    afisare(1,1,1);

    return 0;
}
