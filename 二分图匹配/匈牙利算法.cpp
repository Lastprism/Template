/*

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<cstdlib>
#include<map>

#define LL long long
using namespace std;
const int MAX = 1e5+10;
const LL INF = 0x3f3f3f3f;


vector<int> g[MAX];
int from[MAX],tot;
int vis[MAX];

int match(int x)
{
    for(int i=0;i < g[x].size(); i++)
    {
        int t = g[x][i];
        if(!vis[t])
        {
            vis[t] = 1;
            if(from[t] == -1 || match(t))
            {
                from[t] = x;
                return 1;
            }
        }
    }
    return 0;
}

int hungary()
{
    tot = 0;
    memset(from,0xff,sizeof from);
    for(int i=0;i<n;i++)
    {
        memset(vis,0,sizeof vis);
        if(match(i))
            tot++;
    }
    return tot;
}

int main()
{

	return 0;
}
