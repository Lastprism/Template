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
const int K1 = 1e3+10;
const int MAX = 1e5+10;
const LL INF = 0x3f3f3f3f;
vector< pair<int ,int > >g[MAX];
int n,m;
int dis[MAX];
int vis[MAX];
int mp[K1][K1];
priority_queue<int, vector<int>, greater<int> > pq;

struct cmp
{
    bool operator ()(int &a, int &b) const
    {
        return dis[a]>dis[b];
    }
};
/*
二维数组
void input_array()
{
    for(int i=1;i<=n;i++)
        fill(mp[i]+1,mp[i]+n+1,INF);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        mp[x][y] = min(mp[x][y],z);
        mp[y][x] = min(mp[y][x],z);
    }
}
void dj(int start)
{
    memset(vis,0,sizeof(vis));
    fill(dis+1,dis+n+1,INF);
    dis[start] = 0;
    for(int i=1;i<=n;i++)
    {
        int a = INF;
        int b = -1;
        for(int j=1;j<=n;j++)
        {
            if(dis[j] < a && !vis[j])
            {
                a = dis[j];
                b = j;
            }
        }
        vis[b] = 1;
        //printf("%d\n",b);
        for(int j=1;j<=n;j++)
        {
            if(!vis[j])
                dis[j] = min(dis[j], a + mp[b][j]);
        }
    }
}
*/

//领接表
//用pair.first表示连接的点的编号，pair.second表示长度
void input_table()
{
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        g[x].push_back(make_pair(y,z));
        g[y].push_back(make_pair(x,z));
    }
}
void dj(int start)
{
    memset(vis,0,sizeof(vis));
    fill(dis+1,dis+n+1,INF);
    dis[start] = 0;

    for(int i=1;i<=n;i++)
    {
        int a = INF;
        int b = -1;

        for(int j=1;j<=n;j++)
        {
            if(dis[j] < a && !vis[j])
            {
                a = dis[j];
                b = j;
            }
        }
        vis[b] = 1;
        for(int j=0;j<g[b].size();j++)
        {
            pair<int, int> p = g[b][j];
            if(!vis[p.first])
                dis[p.first] = min(dis[p.first], a + p.second);
        }
    }
}

void djByPq(int start)
{
    while(!pq.empty())
        pq.pop();
    memset(vis,0,sizeof(vis));
    fill(dis+1,dis+n+1,INF);
    dis[start] = 0;
    pq.push(start);
    while(!pq.empty())
    {
        int b = pq.top();
        pq.pop();
        //printf("dis[%d] = %d\n",b,dis[b]);
        for(int i=0; i<g[b].size(); i++)
        {
            pair<int, int> p = g[b][i];
            if(dis[b] + p.second < dis[p.first])
            {
                dis[p.first] = dis[b] + p.second;
                    pq.push(p.first);
            }
        }
    }
}


void print_dis()
{
    for(int i=1;i<=n;i++)
        printf("dis[%d] = %d\n",i,dis[i]);
}
int main()
{
    //freopen("test.txt","r",stdin);
    while(~scanf("%d%d",&m,&n))
    {
        input_table();
        djByPq(n);
        printf("%d\n",dis[1]);
    }
    //fclose(stdout);
	return 0;
}
