/*
*********************************************************************************

n 点数
g g[i]表示从点i连出去的边
返回是否可以拓扑排序
L 返回拓扑排序的结果

***********************************************************************************
*/

const int maxn = 100000+5;
vector<int>g[maxn];
int du[maxn],n,m,L[maxn];
bool toposort()
{
    memset(du,0,sizeof(du));
    for(int i=0;i<n;i++)//数据范围
        for(int j=0;j<g[i].size();j++)
            du[g[i][j]]++;
    int tot = 0;
    queue<int>q;
    for(int i=0;i<n;i++)//数据范围
        if(!du[i])q.push(i);
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        L[tot++] = x;
        for(int j=0;j<g[x].size();j++)
        {
            int t = g[x][j];
            du[t]--;
            if(!du[t])
                q.push(t);
        }
    }
    if(tot == n)return 1;
    return 0;
}
