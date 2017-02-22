#include <bits/stdc++.h>
using namespace std;

ifstream f("summax.in");
ofstream g("summax.out");

const int nmax=2005;
int p,n,a[nmax][nmax],st,dr,i,j;

int trans_lin (int x)
{
    return n-x+1;
}

int trans_col (int x)
{
    return n-x+2;
}

int apartine (int x , int stanga , int dreapta)
{
    if (stanga<=x && x<=dreapta)
     return 1;
    return 0;
}

int main()
{
   f>>p;
   f>>n>>st>>dr;
   for (i=1;i<=n;i++)
    for (j=1;j<=i;j++)
     f>>a[i][j];

   for (i=2;i<=n+1;i++)
    a[1][i]=1;

   for (i=n-1;i>=1;i--)
   {
    for (j=1;j<=i;j++)
    {
       if (a[i+1][j+1]>a[i+1][j])
       {
           a[i][j]+=a[i+1][j+1];

           if ((long long)(a[trans_lin(i)][trans_col(j)])+(long long)(a[trans_lin(i+1)][trans_col(j+1)])>2000000000)
            a[trans_lin(i)][trans_col(j)]=2000000001;
           else
           a[trans_lin(i)][trans_col(j)]+=a[trans_lin(i+1)][trans_col(j+1)];
       }

       if (a[i+1][j]>a[i+1][j+1])
       {
           a[i][j]+=a[i+1][j];

           if ((long long)(a[trans_lin(i)][trans_col(j)])+(long long)(a[trans_lin(i+1)][trans_col(j)])>2000000000)
            a[trans_lin(i)][trans_col(j)]=2000000001;
           else
           a[trans_lin(i)][trans_col(j)]+=a[trans_lin(i+1)][trans_col(j)];
       }

       if (a[i+1][j+1]==a[i+1][j])
       {
           a[i][j]+=a[i+1][j];

           if ((long long)(a[trans_lin(i)][trans_col(j)])+(long long)(a[trans_lin(i+1)][trans_col(j+1)])+(long long)(a[trans_lin(i+1)][trans_col(j)])>2000000000)
            a[trans_lin(i)][trans_col(j)]=2000000001;
           else
           a[trans_lin(i)][trans_col(j)]+=(a[trans_lin(i+1)][trans_col(j+1)]+a[trans_lin(i+1)][trans_col(j)]);
       }
    }
   }

/*
   for (i=1;i<=n;i++)
   {
      for (j=1;j<=n+1;j++)
       g<<a[i][j]<<" ";
     g<<'\n';
   }
*/

   if (p==1)
   {
       g<<a[n][n+1];
       return 0;
   }

   int k;
   int surplus;
   int chosen;
   if (p==2)
   {
       for (k=st;k<=dr;k++)
       {
           surplus=0;
           //g<<"1 "<<'\n';
           g<<"1 ";
           i=1;
           j=1;
           while (i!=n)
           {
               chosen=0;

               if (a[i+1][j]>a[i+1][j+1] && chosen==0)
               {
                   g<<j<<" ";
                   chosen=1;
               }

               if (a[i+1][j+1]>a[i+1][j] && chosen==0)
               {
                   j++;
                   g<<j<<" ";
                   chosen=1;
               }

               if (a[i+1][j+1]==a[i+1][j] && chosen==0)
               {
                   int be,en;
                   be=surplus+a[trans_lin(i+1)][trans_col(j)];
                   if (2000000001-surplus-a[trans_lin(i+1)][trans_col(j+1)]-a[trans_lin(i+1)][trans_col(j)]<0)
                   en=2000000001;
                   else
                   en=surplus+a[trans_lin(i+1)][trans_col(j+1)]+a[trans_lin(i+1)][trans_col(j)];

                   //g<<" ( "<<k<<" "<<be<<" "<<be+1<<" "<<en<<" ) ";

                   if (apartine(k,surplus,be))
                   {
                       g<<j<<" ";
                   }
                   else if (apartine(k,be+1,en))
                   {
                       surplus+=a[trans_lin(i+1)][trans_col(j)];
                       j++;
                       g<<j<<" ";
                   }

                   chosen=1;
               }

               //g<<" ("<<i<<") "<<'\n';

               i++;
               if (i==n)
                g<<'\n';
           }
       }
   }
    return 0;
}
