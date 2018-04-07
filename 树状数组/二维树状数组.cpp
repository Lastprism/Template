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
