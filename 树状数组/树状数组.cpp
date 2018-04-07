#include <cstdio>
#include <cstring>
#define maxn 50047
int c[maxn], a[maxn];
int n,t;
int Lowbit(int x)  // 2^k
{
    return x&(-x);
}
void update(int i, int x)//i点增量为x
{
    while(i <= n)
    {
        c[i] += x;
        i += Lowbit(i);
    }
}
int sum(int x)//区间求和 [1,x]
{
    int sum=0;
    while(x>0)
    {
        sum+=c[x];
        x-=Lowbit(x);
    }
    return sum;
}

int Getsum(int x1,int x2) //求任意区间和
{
    return sum(x2) - sum(x1-1);
}





//二维
int c[M][M];

int lowbit(int x)
{
    return x&(-x);
}

void add(int x,int y,int val)
{
    while(x <= M)
    {
        int y1 = y;
        while(y1 <= M)
        {
            c[x][y1] += val;
            y1 += lowbit(y1);
        }
        x += lowbit(x);
    }
}

int sum(int x,int y)
{
    int ans = 0;
    while(x)
    {
        int y1 = y;
        while(y1)
        {
            ans += c[x][y1];
            y1 -= lowbit(y1);
        }
        x -= lowbit(x);
    }
    return ans;
}
