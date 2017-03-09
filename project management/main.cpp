#include <bits/stdc++.h>
using namespace std;

ifstream f("pm2.in");
ofstream g("pm2.out");

const int nmax=105;
vector <int> graf[nmax];
stack <int> steve;
int cost[nmax];
int sorted[nmax]; /// vectorul sortat topologic
int viz[nmax]; /// vectorul de viz pt sortare topologica
int dp[nmax]; /// dp[sorted[i]] = cat timp consumam pana la sarcina i (sortata topologic) inclusiv
int delay[nmax]; /// timpul maxim pana la finalizarea acestei sarcini inclusiv (incluzand si restul sarcinilor care pot fi finalizate in prealabil)
int not_capat[nmax]; /// pentru nodurile exterioare

void dfs (int node)
{
    viz[node]=1;
    int vecini=graf[node].size();
    int h;

    for (h=0;h<vecini;h++)
        if (viz[graf[node][h]]==0)
             dfs(graf[node][h]);

    steve.push(node);
}

int main()
{
    int n,i,j,parents,node;
    f>>n;

    for (i=1;i<=n;i++)
     f>>cost[i];

    for (i=1;i<=n;i++)
     {
         f>>parents;
         for (j=1;j<=parents;j++)
         {
             f>>node;
             not_capat[node]=1;
             graf[i].push_back(node);
             //graf[node].push_back(i);
         }
     }

     for (i=1;i<=n;i++)
     {
         if (viz[i]==0)
          dfs(i);
     }

     int aux=0;
     while (!steve.empty())
     {
         sorted[n-(++aux)+1]=steve.top();
         steve.pop();
     }

     int parinti,maxim;
     for (i=1;i<=n;i++)
     {
         parinti=graf[sorted[i]].size();
         maxim=0;

         for (j=0;j<parinti;j++)
          if (dp[graf[sorted[i]][j]]>maxim)
           maxim=dp[graf[sorted[i]][j]];

         dp[sorted[i]]=maxim+cost[sorted[i]];
     }

     int cost_maxim=0;
     for (i=1;i<=n;i++)
         cost_maxim=max(dp[i],cost_maxim);

     g<<cost_maxim<<'\n';

     for (i=1;i<=n;i++)
       delay[i]=INT_MAX;

     for (i=n;i>=1;i--)
     {
         if (not_capat[sorted[i]]==0)
             delay[sorted[i]]=cost_maxim;

         parinti=graf[sorted[i]].size();
         for (j=0;j<parinti;j++)
          delay[graf[sorted[i]][j]]=min(delay[graf[sorted[i]][j]],delay[sorted[i]]-cost[sorted[i]]);
     }

     for (i=1;i<=n;i++)
         g<<dp[i]-cost[i]<<" "<<delay[i]-cost[i]<<'\n';

 /*   for (i=1;i<=n;i++)
    g<<sorted[i]<<'\n';*/
    return 0;
}
