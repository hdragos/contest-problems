#include <bits/stdc++.h>
using namespace std;

ifstream f("aiacupalindroame.in");
ofstream g("aiacupalindroame.out");

const int nmax=100005;
vector <int> arb[nmax];
vector <int> muchii[nmax];
int Q,n,ss_ac;
char dic[nmax],superstring[nmax];
int level[nmax],trie_marker,ind_trie[nmax];

struct trie
{
   trie *fiu[27],*tata;
   int ind;
   trie()
   {
       memset(fiu,0,sizeof(fiu));
       tata=0;
       ind=0;
   }

};

trie *root = new trie();
trie *aux_node = root;

int insert_letter(trie *node , char c)
{
    int delta;
    delta = c - 'a';

    if (node->fiu[delta]==NULL)
     node->fiu[delta]= new trie();

    node->fiu[delta]->tata=node;

    node = node->fiu[delta];

    if (node->ind==0)
      node->ind=++trie_marker;

    aux_node=node;

    //g<<c<<" "<<node->ind<<'\n';

    return node->ind;
}

void go_back ()
{
    //g<<aux_node->ind<<" ";
    aux_node= aux_node->tata;
    //g<<aux_node->ind<<'\n';
}

void dfs(int nod , int nivel)
{
    int i,vecini;
    level[nod]=nivel;
    vecini=arb[nod].size();
    for (i=0;i<vecini;i++)
    {
        ind_trie[arb[nod][i]]=insert_letter(aux_node,dic[arb[nod][i]-2]);
        //g<<dic[arb[nod][i]-2]<<'\n';
        dfs(arb[nod][i],nivel+1);
        if (aux_node->ind!=0)
         go_back();
        //g<<aux_node->ind<<'\n';
    }
}

int main()
{
    int i,nod_ac,l;
    f>>n>>Q;
    for (i=2;i<=n;i++)
    {
        f>>nod_ac;
        arb[nod_ac].push_back(i);
    }

    f>>dic;

    dfs(1,1);

    int x,y;

    while (Q--)
    {
        f>>x>>y;

        if (level[x]==level[y] && ind_trie[x]==ind_trie[y])
         g<<"1"<<'\n';
        else
         g<<"0"<<'\n';
    }

    return 0;
}
