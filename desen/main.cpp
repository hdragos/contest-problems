#include <bits/stdc++.h>
using namespace std;
ifstream f("desen.in");
ofstream g("desen.out");
const int nmax=1005;
struct punct {double x,y;};
punct a[nmax];
int parinte[nmax];
int i,j,xac,yac,n,m;
vector <pair <double,pair<int,int> > > apm;
vector <pair <double,pair<int,int> > > aux_apm;

int find_parent (int nod)
{
    if (parinte[nod]==nod)
        return nod;
    return find_parent(parinte[nod]);
}

void unite (int A , int B)
{
    int parA,parB;
    parA=parinte[A];
    parB=parinte[B];
    parA=parinte[parB];
}

double calc_distance (punct A , punct B)
{
    return sqrt( (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y) );
}

void process_apm (int nodes)
{
    int px=0,py=0,h;
    sort(apm.begin(),apm.end());
    double cost_min=0;
    for (h=1;h<=nodes;h++)
      parinte[h]=h;

    for (h=0;h<nodes;h++)
    {
       px=find_parent(apm[h].second.first);
       //py=find_parent(apm[h].second.second);
       /*if (px!=py)
       {
           cost_min+=apm[h].first;
           unite(px,py);
           aux_apm.push_back(apm[h]);
       }*/
    }

    aux_apm=apm;
    g<<setprecision(6)<<fixed;
    g<<cost_min<<'\n';
}

int main()
{

    f>>n;
    for (i=1;i<=n;i++)
    {
        f>>a[i].x>>a[i].y;
        for (j=1;j<i;j++)
        {
           apm.push_back(make_pair(calc_distance(a[i],a[j]),make_pair(i,j)));
        }
        process_apm(i);
    }
    return 0;
}
