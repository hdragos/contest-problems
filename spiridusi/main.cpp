#include <bits/stdc++.h>
using namespace std;
ifstream f("spiridusi.in");
ofstream g("spiridusi.out");
const int nmax=100005;

vector <int> a[nmax]; /// arborele in sine

int val[nmax],sp[nmax],i,j,n,kmax,x,y,rmq[22][nmax],profit[nmax],cost[nmax],dp_siz,loga[nmax],sol=-1;
bool viz[nmax];
/// val[i] = coeficient de placere al camerei i;
/// sp[i] = nr de spiridusi in camera i;
/// profit[i] = coeficientele de placere insumate de la nodul 1 pana la nodul i (sume partiale)
/// cost[i] = nr de spiridusi omorati insumati de la nodul 1 pana la nodul i (sume partiale)
/// rmq[k][i] = minimul (din profit) din intervalul incepand de la i de lungime 2^k

int bin_search (int ind) /// sa cautam binar punctul A , dupa costul de spiridusi omorati
{
   int dr,mij,st;
   st=-1;
   dr=ind+1;
   while (dr-st>1)
   {
       mij=(st+dr)/2;
       if (cost[ind]-cost[mij]<=kmax)
        dr=mij;
       else
        st=mij;
   }
   if (dr>=ind)
     return -1;
   if (cost[ind]-cost[dr]<=kmax)
    return dr;
   return -1;
}

int query (int y, int x)
{
    int dif=loga[y-x+1];
    return min(rmq[dif][y],rmq[dif][x-(1<<(dif))+1]);
}

int dfs (int nod ,int ind)
{
    /// parcurgem cu un dfs tot arborele , si ne contstruim efectiv lantul A - B , B fiind nodul actual si A fiind gasit prin cautare binara
    /// in prealabil , stim ca avem lant , deci putem construi vectorii profit si cost
      int h,mx,nou,poz;
      profit[ind]=profit[ind-1]+val[nod];
      cost[ind]=cost[ind-1]+sp[nod];

      poz=bin_search(ind); /// cautam nodul A (pentru ca nodul B este nodul in care ne aflam)

      rmq[0][ind]=profit[ind];
      for (h=1;ind>(1<<h);h++) /// facem minimul din profit (adica sa vedem care va fi cel mai mic profit pe care trebuie sa-l scadem , putem avea si valori de placere negative*)
      {
        if(rmq[h-1][ind]<rmq[h-1][ind-(1<<(h-1))])
        {
            rmq[h][ind]=rmq[h-1][ind];
        }
        else
        {
            rmq[h][ind]=rmq[h-1][ind-(1<<(h-1))];
        }
      }

      if(poz!=-1) /// vedem daca am gasit un nod A (inceputul lantului)
      {
        mx=query(poz,ind-1); /// vedem profitul minim pe care il vom scadea
        sol=max(profit[ind]-mx,sol); /// updatam solutia daca e nevoie
      }

      viz[nod]=1; /// continuam dfs-ul
      for(h=0;h<a[nod].size();h++)
      {
        nou=a[nod][h];
        if(!viz[nou])
        {
            dfs(nou,ind+1);
        }
      }
}

int main()
{
    f>>n>>kmax;

    for(int j = 0; j < 21; j++)
    {
        for(i = 0; i < n; i++)
        {
           rmq[j][i] = (1<<30);
        }
    }

    for (i=1;i<=n;i++)
        f>>sp[i];

    for (i=1;i<=n;i++)
        f>>val[i];

    for (i=2;i<=n;i++)
        loga[i]=loga[i/2]+1;

    for (i=1;i<n;i++)
    {
        f>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }

    dfs(1,1);
    g<<sol;

    return 0;
}
