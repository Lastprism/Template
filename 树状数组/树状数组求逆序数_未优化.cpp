#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
using namespace std;

const int M = 3000000+10;
int n;
int c[M];
int v[M];
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
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&v[i]);
            ans += sum(v[i]-1);
            add(v[i],1);
        }
    return 0;
}
