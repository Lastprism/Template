/*-------------------------------------------------------------------------------------------------------------------
@线段树单点覆盖区间更新（时间复杂度）

----------------------------------------------------------------------------------------------------------------------*/

#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int maxn = 100007;
const int INF=0x7fffffff;
int MAX[maxn<<2];
int MIN[maxn<<2];
int SUM[maxn<<2];
void PushUP(int rt) {
    MAX[rt] = max(MAX[rt<<1] , MAX[rt<<1|1]);
    MIN[rt] = min(MIN[rt<<1] , MIN[rt<<1|1]);
    SUM[rt] = SUM[rt<<1] + SUM[rt<<1|1];
}
//所有的 l ,r ,rt 参数为 1，n,1   其中n为区间长度
void build(int l,int r,int rt) {   //建树
    if (l == r) {
        MAX[rt] = MIN[rt] =SUM[rt]=0;  //初始化线段树为0的写法
        /*
          //边读入边建树的写法，复杂度O(n)  若执行n次更新来初始化的话复杂度为O（nlogn）
            scanf("%d",&MAX[rt]);
            MIN[rt] = MAX[rt];
            SUM[rt] = MAX[rt];
        */
        return ;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    PushUP(rt);
}
void update(int p,int v,int l,int r,int rt) {  //单点替换，把p位置的值置为v
    if (l == r) {
        MAX[rt] = v;
        MIN[rt] = v;
        SUM[rt] = v;
        return ;
    }
    int m = (l + r) >> 1;
    if (p <= m) update(p , v ,lson);
    else update(p , v , rson);
    PushUP(rt);
}
void update1(int p,int addv,int l,int r,int rt) {  //单点增加，把p位置的值增加v
    if (l == r) {
        SUM[rt] = SUM[rt] + addv;
        MIN[rt] = MIN[rt] + addv;
        MAX[rt] =MAX[rt]+addv;
        return ;
    }
    int m = (l + r) >> 1;
    if (p <= m) update1(p , addv ,lson);
    else update1(p , addv , rson);
    PushUP(rt);
}
int queryMAX(int L,int R,int l,int r,int rt) {   //求L~R的最大值
    if (L <= l && r <= R) {
        return MAX[rt];
    }
    int m = (l + r) >> 1;
    int ret = -INF;
    if (L <= m) ret = max(ret , queryMAX(L , R , lson));
    if (R > m)  ret =  max(ret , queryMAX(L , R , rson));
    return ret;
}
int queryMIN(int L,int R,int l,int r,int rt) {  //求L~R的最小值
    if (L <= l && r <= R) {
        return MIN[rt];
    }
    int m = (l + r) >> 1;
    int ret = INF;
    if (L <= m) ret = min(ret , queryMIN(L , R , lson));
    if (R > m)  ret =  min(ret , queryMIN(L , R , rson));
    return ret;
}
int querySUM(int L,int R,int l,int r,int rt) {   //求L~R的和
    if (L <= l && r <= R) {
        return SUM[rt];
    }
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m) ret += querySUM(L , R , lson);
    if (R > m)  ret +=  querySUM(L , R , rson);
    return ret;
}
int main() {
    int n , m;
    while (~scanf("%d%d",&n,&m)) {
        build(1 , n , 1);
        while (m --) {
            char op[2];
            int a , b;
            scanf("%s%d%d",op,&a,&b);
            if (op[0] == 'Q') { //区间求最大
                printf("%d\n",queryMAX(a , b , 1 , n , 1));
            } else if(op[0]=='U') //单点替换
                update(a , b , 1 , n , 1);
            else if(op[0]=='M') { //区间求最小
                printf("%d\n",queryMIN(a , b , 1 , n , 1));
            } else if(op[0]=='H') { //区间求和
                printf("%d\n",querySUM(a , b , 1 , n , 1));
            } else if(op[0]=='S') { //单点增加
                update1(a , b , 1 , n , 1);
            } else if(op[0]=='E') { //单点减少
                update1(a , -b , 1 , n , 1);
            }
        }
    }
    return 0;
}
