#include <bits/stdc++.h>
#define eps 1e-12
using namespace std;
ifstream f("gradina.in");
ofstream g("gradina.out");
const int nmax = 255;
struct punct {long long x,y,ini;} a[nmax]; /// am pus si ini pt ca ne va ajuta la secventa minima din pdv lexicografic
int n,st_siz,dr_siz,ord_dr_siz,ord_st_siz;
long double difmin=INT_MAX,ar1,ar2;
int parte[nmax];
punct P1,P2;
char fin[nmax],auxr[nmax];
punct st[nmax],dr[nmax],stiv1[nmax],stiv2[nmax],ord_st[nmax],ord_dr[nmax];

bool cmp (punct A , punct B) /// functia de comparare
{
    if (A.x!=B.x) return A.x<B.x;
    return A.y<B.y;
}

int cross_product (punct O,punct A ,punct B) /// cross product , pentru trasare de dreapta si sa vedem pozitia unui punct fata de o dreapta
{
    A.x-=O.x;
    A.y-=O.y;
    B.x-=O.x;
    B.y-=O.y;
    return A.x*B.y-A.y*B.x;
}

void create_answer () /// creeaza vectorul de I si V , minim lexicografic
{
    int i;
    int verif;
    verif=parte[1];
    for (i=1;i<=n;i++)
    {
        if (parte[i]==verif)
            auxr[i-1]='I';
        else
            auxr[i-1]='V';
    }

    auxr[n]=NULL;
}

double arie (punct V[nmax],int V_siz) /// aria , merge doar pe vector de puncte ordonate in sens trigonometric (sau invers)
{
    long double sol=0;
    int h;
    for (h=1;h<V_siz;h++)
     sol+=V[h].x*V[h+1].y-V[h+1].x*V[h].y;

    sol+=V[V_siz].x*V[1].y-V[1].x*V[V_siz].y;

    sol=fabs(sol);

    return sol;
}

void draw_line (punct A , punct B , int ind_A , int ind_B , int sens) /// functia de trasarea dreapta , intre punctele A si B , (cand sens==1 , pune punctul A in stanga si B in dreapta; pt sens==0 face vice-versa)
{
    int i;
    long long aux;
    P1=A; P2=B;
    st_siz=0;
    dr_siz=0;
    for (i=1;i<=n;i++)
    {
        if (i!=ind_A && i!=ind_B)
        {
          aux=cross_product(a[i],A,B);
          if (aux<eps)
          {
           st[++st_siz]=a[i];
           parte[a[i].ini]=0;
          }
          if (aux>eps)
          {
           dr[++dr_siz]=a[i];
           parte[a[i].ini]=1;
          }
        }

        if (i==ind_A)
        {
            if (sens==1)
            {
                parte[a[i].ini]=0;
                st[++st_siz]=A;
            }
            else
            {
                parte[a[i].ini]=1;
                dr[++dr_siz]=A;
            }
        }

        if (i==ind_B)
        {
            if (sens==1)
            {
                parte[a[i].ini]=1;
                dr[++dr_siz]=B;
            }
            else
            {
                parte[a[i].ini]=0;
                st[++st_siz]=B;
            }
        }

    }

}

bool convex_hull (punct V[nmax] , int V_siz , punct R[nmax] , int &R_siz) /// infasuratoare convexa cu parametrii , V fiind vectorul cu puncte , iar R vectorul in care va fii raspunsul
{
    if (V_siz<3)
        return 0;
    int h,auxsiz=0,stiv1_size,stiv2_size;

    stiv1[1]=V[1];
    stiv1[2]=V[2];
    stiv1_size=2;

    for (h=3;h<=V_siz;h++)
    {
        while (stiv1_size>=2 && cross_product(stiv1[stiv1_size-1],stiv1[stiv1_size],V[h])<eps)
         stiv1_size--;
        stiv1[++stiv1_size]=V[h];
    }

    stiv2_size=2;
    stiv2[1]=V[V_siz];
    stiv2[2]=V[V_siz-1];

    for (h=V_siz-2;h>=1;h--)
    {
        while (stiv2_size>=2 && cross_product(stiv2[stiv2_size-1],stiv2[stiv2_size],V[h])<eps)
         stiv2_size--;
        stiv2[++stiv2_size]=V[h];
    }

    for (h=1;h<=stiv1_size;h++)
       R[++auxsiz]=stiv1[h];

    for (h=2;h<stiv2_size;h++)
     R[++auxsiz]=stiv2[h];

     if (auxsiz!=V_siz)
      return 0;

    R_siz=auxsiz;

    return 1;
}

int main() /// 5 ore in total. never again.
{
    int i,j,h;
    f>>n;
    for (i=1;i<=n;i++)
    {
        f>>a[i].x>>a[i].y;
        a[i].ini=i;
    }

    sort(a+1,a+1+n,cmp);

    for (i=0;i<n;i++)
        fin[i]='V';
    fin[n]=NULL;

    for (i=1;i<n;i++)
        for (j=i+1;j<=n;j++)
        {
           draw_line(a[i],a[j],i,j,0);
           if (convex_hull(st,st_siz,ord_st,ord_st_siz) && convex_hull(dr,dr_siz,ord_dr,ord_dr_siz))
           {
               ar1=arie(ord_st,ord_st_siz);
               ar2=arie(ord_dr,ord_dr_siz);
               if (fabs(ar1-ar2)==difmin)
               {
                   create_answer();
                   if (strcmp(auxr,fin)<0)
                     strcpy(fin,auxr);
               }

               if (fabs(ar1-ar2)<difmin)
               {
                   create_answer();
                   difmin=fabs(ar1-ar2);
                    strcpy(fin,auxr);
               }
           }

           draw_line(a[i],a[j],i,j,1);
           if (convex_hull(st,st_siz,ord_st,ord_st_siz) && convex_hull(dr,dr_siz,ord_dr,ord_dr_siz))
           {
               ar1=arie(ord_st,ord_st_siz);
               ar2=arie(ord_dr,ord_dr_siz);
               if (fabs(ar1-ar2)==difmin)
               {
                   create_answer();
                   if (strcmp(auxr,fin)<0)
                     strcpy(fin,auxr);
               }

               if (fabs(ar1-ar2)<difmin)
               {
                   create_answer();
                   difmin=fabs(ar1-ar2);
                    strcpy(fin,auxr);
               }
           }
        }

    g<<setprecision(1)<<fixed;
    g<<difmin*0.5<<'\n';
    g<<fin;

    return 0;
}
