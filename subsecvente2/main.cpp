#include <string.h>
#include <fstream>
using namespace std;
ifstream f("subsecvente2.in");
ofstream g("subsecvente2.out");
const int nmax=100005;
struct trie
{
    int fr;
    trie *fiu[2];
    trie ()
    {
      fr=0;
      memset(fiu,0,sizeof(fiu));
    }
};

int n,i,j,lg,ras;
char a[nmax],s[nmax];
trie *root = new trie();

void insert_word (trie *node, char *s , int level)
{
    int delta;
    if (node->fr==i-1)
    {
        node->fr++;
        if (node->fr==n)
            ras=max(ras,level);
    }

    if (*s==NULL)
        return;

    delta=*s - 'a';

    if (node->fiu[delta] == NULL)
       node->fiu[delta]=new trie();

    insert_word(node->fiu[delta],s+1,level+1);
}

int main()
{
    f>>n;
    for (i=1;i<=n;i++)
    {
        f>>s;
        lg=strlen(s);
        for (j=0;j<lg;j++)
        {
            strncpy(a,s+j,60);
            insert_word(root,a,0);
        }
    }

    g<<ras;
}
