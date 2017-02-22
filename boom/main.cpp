#include <bits/stdc++.h>
using namespace std;

ifstream f("boom.in");
ofstream g("boom.out");

/// 111...1 e starea initiala , 000...0 e starea finala , 1 pt camera unde poate fi sobolanul , 0 unde nu poate fi
/// dijkstra , fiecare bomba e o muchie , fiecare stare e un nod

const int logmax=(1<<20)+5;
const int nmax=22;

int n,m;
int dp[logmax]; /// dp[i] = costul minim pana in starea i

struct bombaa {int cost,mask;};

pair <int,int> parinte[logmax]; /// pt afisare , primul camp e pentru configuratie , al doilea pentru indicele sarjei
vector <bombaa> sarje;
priority_queue < pair<int,int> , vector <pair <int,int> > , greater < pair <int,int> > > cod; /// cost , new state

void dijkstra()
{
    int i,cost,conf,cur_cost,cur_conf; /// cur_conf e pentru configuratie curenta (sau nod curent)
    bombaa c4;
    while (!cod.empty())
    {
        cost=cod.top().first;
        conf=cod.top().second;
        cod.pop();
        for (i=0;i<m;i++)
        {
           cur_conf=sarje[i].mask;
           cur_cost=sarje[i].cost;

           cur_conf = ((conf) & (cur_conf));
           cur_conf = (((cur_conf)<<1) | ((cur_conf)>>1));
           cur_conf = (((1<<(n))-1) & (cur_conf));

           cur_cost+=cost;

           if (dp[cur_conf]>cur_cost)
           {
               dp[cur_conf]=cur_cost;
               parinte[cur_conf]=make_pair(conf,i+1);
               cod.push(make_pair(cur_cost,cur_conf));
           }
        }
    }
}

void afisare (int conf , int nr_bombe)
{
    if (conf==((1<<(n))-1))
    {
        g<<nr_bombe<<'\n';
    }
    else
    {
        afisare(parinte[conf].first,nr_bombe+1);
        g<<parinte[conf].second<<'\n';
    }
}

int main()
{
    int i,j,rooms,aux,cur_conf,cur_cost;
    bombaa c4;
    f>>n>>m;

    aux=(1<<(n))-1;

    for (i=0;i<=aux;i++)
        dp[i]=INT_MAX;

    for (i=1;i<=m;i++)
    {
        f>>cur_cost>>rooms;

        cur_conf=(1<<(n))-1;

        for (j=1;j<=rooms;j++)
        {
            f>>aux;
            cur_conf=(cur_conf)^((1<<(aux-1)));
        }

        c4.cost=cur_cost;
        c4.mask=cur_conf;

        sarje.push_back(c4);

    }

    dp[(1<<(n))-1]=0;
    cod.push(make_pair(0,(1<<(n))-1));
    dijkstra();

    g<<dp[0]<<'\n';

    afisare(0,0);

    return 0;
}
