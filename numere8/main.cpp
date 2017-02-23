#include <fstream>
using namespace std;

ifstream f("numere8.in");
ofstream g("numere8.out");
/// vom folosi baza 3 pt aceasta problema , 0 pt element exclus , 1 pt element in prima multime disjuncta , 2 pt element in a doua multime disjuncta
int summax,confmax,n,nrsol,u;
int a[15];

int main()
{
    int i,j,k,sum1,sum2,cpi;
    for (i=0;i<=9;i++)
        f>>a[i];

    for (i=0;i<59049;i++)
    {
        sum1=0;
        sum2=0;

        cpi=i;
        j=0;
        while (j<=9) /// parcurgem cei 10 biti in baza 3
        {
            u=cpi%3;
            cpi/=3;
            if (u==1)
               sum1+=a[j];
            if (u==2)
               sum2+=a[j];
            j++;
        }

        //g<<sum1<<" "<<sum2<<'\n';

        if (sum1==sum2)
        {
            nrsol++;
            if (summax<sum1)
            {
                summax=sum1;
                confmax=i;
            }
        }

    }

    nrsol--; /// scadem prima suma in care ambele submultimi sunt nenule
    nrsol/=2; /// orice suma o sa apara de 2 ori , de asta impartim la 2

    g<<nrsol<<" "<<summax<<'\n';

    cpi=confmax;
    j=0;
    while (j<=9) /// afisarea primei multimi
    {
        u=cpi%3;
        cpi/=3;
        if (u==1)
            g<<a[j]<<" ";
        j++;
    }

    g<<'\n';

    cpi=confmax;
    j=0;
    while (j<=9) /// afisarea celei dea doua multimi
    {
        u=cpi%3;
        cpi/=3;
        if (u==2)
            g<<a[j]<<" ";
        j++;
    }

    return 0;
}
