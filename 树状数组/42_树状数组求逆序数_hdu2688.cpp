//hdu2688
//树状数组求逆序数
/*
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
using namespace std;

const int M = 3000000+10;
int n;
struct Node
{
    int value;
    int id;
}node[M];
int c[M];
int reflect[M];

int cmp(Node x,Node y)
{
    return x.value<y.value;
}
int lowbit(int x)
{
    return x&(-x);
}
void add(int pos,int value)
{
    int x = pos;
    while(x<=n)
    {
        c[x] += value;
        x += lowbit(x);
    }
}
ll sum(int pos)
{
    ll ans = 0;
    int x = pos;
    while(x>0)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}
int main()
{
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&node[i].value);
            node[i].id = i;
        }
        sort(node,node+n,cmp);
        int id = 1;
        reflect[node[1].id] = 1;
        for(int i=2;i<=n;i++)
        {
            if(node[i].value == node[i-1].value)
                reflect[node[i].id] = id;
            else
                reflect[node[i].id] = ++id;
        }
        memset(c,0,sizeof c);
        ll ans = 0;
        for(int i=1;i<=n;i++)
        {
            add(reflect[i],1);
            ans += sum(reflect[i]) - 1;
        }
        int m;
        cin>>m;
        while(m--)
        {
            char s;
            cin>>s;
            if(s == 'Q')
            {
                printf("%lld\n",ans);
            }
            else if(s == 'R')
            {
                int x,y;
                scanf("%d%d",&x,&y);
                int tmp = reflect[x+1];
                for(int i=x+2;i<=y+1;i++)
                {
                    if(reflect[i]<tmp)
                        ans++;
                    else
                        ans--;
                    reflect[i-1] = reflect[i];
                }
                reflect[y+1] = tmp;
            }
        }
    }
}
*/
//hdu2688
//树状数组求逆序数
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
using namespace std;

const int M = 3000000+10;
const int maxn = 10001;
int n;
int c[maxn];
int v[M];
int lowbit(int x)
{
    return x&(-x);
}
void add(int pos,int value)
{
    while(pos<maxn)
    {
        c[pos] += value;
        pos += lowbit(pos);
    }
}
ll sum(int pos)
{
    ll ans = 0;
    while(pos)
    {
        ans += c[pos];
        pos -= lowbit(pos);
    }
    return ans;
}
int m;
int main()
{
    while(~scanf("%d",&n))
    {
        memset(c,0,sizeof c);
        ll ans = 0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&v[i]);
            ans += sum(v[i]-1);
            add(v[i],1);
        }
        scanf("%d",&m);
        while(m--)
        {
            char s[1];
            scanf("%s",s);
            if(s[0] == 'Q')
                printf("%lld\n",ans);
            else
            {
                int x,y;
                scanf("%d%d",&x,&y);
                int tmp = v[x+1];
                for(int i=x+2;i<=y+1;i++)
                {
                    if(v[i]<tmp)
                        ans++;
                    if(v[i]>tmp)
                        ans--;
                    v[i-1] = v[i];
                }
                v[y+1] = tmp;
            }
        }
    }
}

