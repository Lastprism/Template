/*
    Problem: JZOJ1598(ѯ��һ���ַ������ж������ٳ������ε��Ӵ�)
    Content: SA's Code and Explanation
    Author : YxuanwKeith
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include<queue>
#include<iostream>
#define rank rankk
using namespace std;

const int MAXN = 2000000+10;

char ch[MAXN], All[MAXN];
int SA[MAXN], rank[MAXN], Height[MAXN], tax[MAXN], tp[MAXN], a[MAXN], n, m;
char str[MAXN];
//rank[i] ��i����׺������; SA[i] ����Ϊi�ĺ�׺λ��; Height[i] ����Ϊi�ĺ�׺������Ϊ(i-1)�ĺ�׺��LCP
//tax[i] ��������������; tp[i] rank�ĸ�������(���������еĵڶ��ؼ���),��SA����һ����
//aΪԭ��
void RSort() {
    //rank��һ�ؼ���,tp�ڶ��ؼ��֡�
    for (int i = 0; i <= m; i ++) tax[i] = 0;
    for (int i = 1; i <= n; i ++) tax[rank[tp[i]]] ++;
    for (int i = 1; i <= m; i ++) tax[i] += tax[i-1];
    for (int i = n; i >= 1; i --) SA[tax[rank[tp[i]]] --] = tp[i]; //ȷ�������һ�ؼ��ֵ�ͬʱ��������ڶ��ؼ��ֵ�Ҫ��
} //��������,���µĶ�Ԫ������

int cmp(int *f, int x, int y, int w) { return f[x] == f[y] && f[x + w] == f[y + w]; }
//ͨ����Ԫ�������±�ıȽϣ�ȷ�������Ӵ��Ƿ���ͬ

void Suffix() {
    //SA
    for (int i = 1; i <= n; i ++) rank[i] = a[i], tp[i] = i;
    m = 127 ,RSort(); //һ��ʼ���Ե����ַ�Ϊ��λ������(m = 127)

    for (int w = 1, p = 1, i; p < n; w += w, m = p) { //���Ӵ����ȷ���,����rank

        //w ��ǰһ���Ӵ��ĳ���; m ��ǰ��ɢ�������������
        //��ǰ��tp(�ڶ��ؼ���)��ֱ������һ�ε�SA�ĵõ�
        for (p = 0, i = n - w + 1; i <= n; i ++) tp[++ p] = i; //����Խ��,�ڶ��ؼ���Ϊ0
        for (i = 1; i <= n; i ++) if (SA[i] > w) tp[++ p] = SA[i] - w;

        //����SAֵ,����tp��ʱ������һ�ֵ�rank(����cmp�Ƚ�)
        RSort(), swap(rank, tp), rank[SA[1]] = p = 1;

        //���Ѿ���ɵ�SA���������������rank,����ɢrank
        for (i = 2; i <= n; i ++) rank[SA[i]] = cmp(tp, SA[i], SA[i - 1], w) ? p : ++ p;
    }
    //��ɢ������ȵ��ַ�����rank��Ϊ��ͬ��
    //LCP
    int j, k = 0;
    for(int i = 1; i <= n; Height[rank[i ++]] = k)
        for( k = k ? k - 1 : k, j = SA[rank[i] - 1]; a[i + k] == a[j + k]; ++ k);
    //���֪��ԭ���ͱȽϺ�������
}

void Init() {
    scanf("%s", str);
    n = strlen(str);
    for (int i = 0; i < n; i ++) a[i + 1] = str[i];
}
struct cmp1{
    bool operator ()(int &a,int &b){
        return a>b;//��Сֵ����
    }
};

int cnt[MAXN];
int main() {
    int t;
    scanf("%d",&t);
    while(t--){
        priority_queue<int,vector<int>,cmp1>q;
        int tot= 0;
        int k;
        scanf("%d",&k);
        Init();
        Suffix();
        int ans = 0;
        for(int i=2;i<=n;i++)
        {
            if(i<k)
            {
                q.push(Height[i]);
                continue;
            }
            q.push(Height[i]);
            cnt[tot++] = q.top();
            q.pop();
        }
        for()
        ans += cnt[0];
        for (int i = 1; i < tot; i ++)
        {
            //cout<<cnt[i]<<" "<<cnt[i-1]<<endl;
            if(cnt[i]*k <= n)
                ans += max(cnt[i] - cnt[i - 1], 0);
        }
        printf("%d\n", ans);
    }
}
int minm = height[2],id=2;
for(int i=3;i<k;i++)
    if(height[i]<minm)
        minm = height[i];
for(int i=k;i<=n;i++)
{
    minm = height[i];
    for(int j=i-k+2;j<i;j++)
    {
        if(heigh[j]<minm)
            minm = height[j];
    }
}

