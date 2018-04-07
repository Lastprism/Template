/*-------------------------------------------------------------------------------------------------------------------
@�߶������㸲��������£�ʱ�临�Ӷȣ�

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
//���е� l ,r ,rt ����Ϊ 1��n,1   ����nΪ���䳤��
void build(int l,int r,int rt) {   //����
    if (l == r) {
        MAX[rt] = MIN[rt] =SUM[rt]=0;  //��ʼ���߶���Ϊ0��д��
        /*
          //�߶���߽�����д�������Ӷ�O(n)  ��ִ��n�θ�������ʼ���Ļ����Ӷ�ΪO��nlogn��
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
void update(int p,int v,int l,int r,int rt) {  //�����滻����pλ�õ�ֵ��Ϊv
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
void update1(int p,int addv,int l,int r,int rt) {  //�������ӣ���pλ�õ�ֵ����v
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
int queryMAX(int L,int R,int l,int r,int rt) {   //��L~R�����ֵ
    if (L <= l && r <= R) {
        return MAX[rt];
    }
    int m = (l + r) >> 1;
    int ret = -INF;
    if (L <= m) ret = max(ret , queryMAX(L , R , lson));
    if (R > m)  ret =  max(ret , queryMAX(L , R , rson));
    return ret;
}
int queryMIN(int L,int R,int l,int r,int rt) {  //��L~R����Сֵ
    if (L <= l && r <= R) {
        return MIN[rt];
    }
    int m = (l + r) >> 1;
    int ret = INF;
    if (L <= m) ret = min(ret , queryMIN(L , R , lson));
    if (R > m)  ret =  min(ret , queryMIN(L , R , rson));
    return ret;
}
int querySUM(int L,int R,int l,int r,int rt) {   //��L~R�ĺ�
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
            if (op[0] == 'Q') { //���������
                printf("%d\n",queryMAX(a , b , 1 , n , 1));
            } else if(op[0]=='U') //�����滻
                update(a , b , 1 , n , 1);
            else if(op[0]=='M') { //��������С
                printf("%d\n",queryMIN(a , b , 1 , n , 1));
            } else if(op[0]=='H') { //�������
                printf("%d\n",querySUM(a , b , 1 , n , 1));
            } else if(op[0]=='S') { //��������
                update1(a , b , 1 , n , 1);
            } else if(op[0]=='E') { //�������
                update1(a , -b , 1 , n , 1);
            }
        }
    }
    return 0;
}
