//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<string>
#include<algorithm>
#include<cmath>
#define INF 0x3f3f3f
#define MAX 1000+10

using namespace std;

int v[MAX];
int g[MAX][MAX];
int dis[MAX];
int n,m;

void dijkstra()
{
    for(int i = 1;i <= n;i ++ )
        dis[i] = INF;
    memset(v,0,sizeof(v));
    dis[n] = 0;
    for(int i=1;i<=n;i++)
    {
        int mark = -1,mindis = INF;
        for(int j=1;j<=n;j++)
        {
            if(!v[j] && dis[j] < mindis)
            {
                mark = j;
                mindis = dis[j];
            }
        }
        v[mark] = 1;
        for(int j=1;j<=n;j++)
        {
            if(!v[j])
                dis[j] = min(dis[mark] + g[mark][j],dis[j]);
        }
    }
}
int main()
{
    while(~scanf("%d%d",&m,&n))
    {
        if(n ==0 && m == 0)
            break;
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)
                g[i][j] = INF;
        int x,y,z;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            g[x][y] = z;
            g[y][x] = z;
        }
        dijkstra();
        printf("%d\n",dis[1]);
    }
    return 0;
}
