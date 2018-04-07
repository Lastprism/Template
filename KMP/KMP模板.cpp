/*-------------------------------------------------------------------------------------------------------------------
@KMP（O（N+M））
匹配模式串是否在字符串中出现，如果出现返回出现的位置
----------------------------------------------------------------------------------------------------------------------*/

#include<stdio.h>
#include<string.h>
const int M = 10005;    //模式串长度
const int MAX = 1000000+10;     //带匹配的字符串长度
char p[M],t[MAX];
int next[M];            //next 数组
//P模式串 next next数组
void makeNext(const char P[],int next[])
{
    int q,k;
    int m = strlen(P);
    next[0] = 0;
    for (q = 1,k = 0; q < m; ++q)
    {
        while(k > 0 && P[q] != P[k])    k = next[k-1];
        if (P[q] == P[k])   k++;
        next[q] = k;
    }
}
//T带匹配的字符串 P模式串 next数组
int kmp(const char T[],const char P[],int next[])
{
    int ans = 0;
    int n,m;
    int i,q;
    n = strlen(T);
    m = strlen(P);
    makeNext(P,next);
    for (i = 0,q = 0; i < n; ++i)
    {
        while(q > 0 && P[q] != T[i])    q = next[q-1];
        if (P[q] == T[i])   q++;
        if (q == m)     ans ++;
    }
    return ans;
}

int main()
{
    int N;
    scanf("%d",&N);
    while(N--)
    {
        scanf("%s%s",p,t);
        printf("%d\n",kmp(t,p,next));
    }
    return 0;
}
