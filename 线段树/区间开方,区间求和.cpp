#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include<math.h>
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
#define ll long long
const int maxn = 100100;
using namespace std;
ll SUM[maxn<<2];
int cnt[maxn<<2];//0��ʾ�������ֵ������1��1��ʾ�������ֵ����1
void PushUp(int rt) { //�����ӡ��Һ������ϸ��¸��ڵ�
    SUM[rt] = SUM[rt<<1] + SUM[rt<<1|1];
    cnt[rt] = cnt[rt<<1]&cnt[rt<<1|1];
}
//���е�l��r��rt  ����1��n��1
void build(int l,int r,int rt) { //��ʼ������
    cnt[rt] = 0;
    if (l== r) {
        scanf("%lld",&SUM[rt]);  //�߶���߽����ķ���
        if(SUM[rt]==1)
            cnt[rt] = 1;
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void update(int L,int R,int l,int r,int rt) { //��L~R�����ֵ����
    if(cnt[rt])return;
    if (l == r) {
        SUM[rt] =(ll)sqrt(SUM[rt]*1.0);
        if(SUM[rt] == 1)
            cnt[rt] = 1;
        return ;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , lson);
    if (R > m) update(L , R , rson);
    PushUp(rt);
}
ll querySUM(int L,int R,int l,int r,int rt) {  //������L~R�ĺ�
    if (L <= l && r <= R)
        return SUM[rt];
    int m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m) ret += querySUM(L , R , lson);
    if (m < R) ret += querySUM(L , R , rson);
    return ret;
}
int main()
{
    int n;
    int Case = 1;
    while(~scanf("%d",&n))
    {
        build(1,n,1);
        int m;
        scanf("%d",&m);
        printf("Case #%d:\n",Case++);
        for(int i=0;i<m;i++)
        {
            int q,x,y;
            scanf("%d%d%d",&q,&x,&y);
            if(x>y)
            {
                int tmp = x;
                x = y;
                y = tmp;
            }
            if(q==1)
            {
                ll ans = querySUM(x,y,1,n,1);
                printf("%lld\n",ans);
            }
            else
            {
                update(x,y,1,n,1);
            }
        }
        cout<<endl;
    }
}
