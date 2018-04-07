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
int cnt[maxn<<2];//0表示该区间的值不都是1，1表示该区间的值都是1
void PushUp(int rt) { //由左孩子、右孩子向上更新父节点
    SUM[rt] = SUM[rt<<1] + SUM[rt<<1|1];
    cnt[rt] = cnt[rt<<1]&cnt[rt<<1|1];
}
//所有的l，r，rt  带入1，n，1
void build(int l,int r,int rt) { //初始化建树
    cnt[rt] = 0;
    if (l== r) {
        scanf("%lld",&SUM[rt]);  //边读入边建树的方法
        if(SUM[rt]==1)
            cnt[rt] = 1;
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void update(int L,int R,int l,int r,int rt) { //将L~R区间的值开方
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
ll querySUM(int L,int R,int l,int r,int rt) {  //求区间L~R的和
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
