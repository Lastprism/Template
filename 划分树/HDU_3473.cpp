#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 1e5+10;
typedef long long LL;
int sorted[N];
struct Node
{
    int value[N];   //第k层当前位置元素的值
    int num[N];     //num记录元素所在区间的当前位置之前进入左孩子的个数
    LL sum[N];      //sum记录当前位置之前进入左孩子个数的和
}t[40];
LL ssum[N];
LL tsum;
void build(int l,int r,int ind)
{
    if (l == r) return ;
    int mid = (l+r)/2;
    int isame = mid - l + 1,same = 0;   //isame是与sorted[mid]相等且分到做孩子的个数，左孩子总共有mid-l+1个数，减去<sorted[mid]就是与sorted[mid]相等且分到左孩子的个数
    for(int i = l; i <= r; i ++)
        if(t[ind].value[i] < sorted[mid]) isame--;
    int ln = l, rn = mid + 1 ;
    for(int i = l; i <= r; i++)
    {
        //初始化
        if(i == l)
            t[ind].num[i] = 0, t[ind].sum[i] = 0;
        else
            t[ind].num[i] = t[ind].num[i-1], t[ind].sum[i] = t[ind].sum[i-1];
        //小于sorted[mid]进入做孩子，num[i]++,sum[i]+=value[i],ind+1层的value[ln] = ind 层的value[i]
        if(t[ind].value[i] < sorted[mid])
        {
            t[ind].num[i] ++;
            t[ind].sum[i] += t[ind].value[i];
            t[ind + 1].value[ln++] = t[ind].value[i];
        }
        else if(t[ind].value[i] > sorted[mid])
            t[ind+1].value[rn++] = t[ind].value[i];
        else
            if(same < isame)
            {
                same ++ ;
                t[ind].num[i]++;
                t[ind].sum[i] += t[ind].value[i];
                t[ind+1].value[ln++] = t[ind].value[i];
            }
            else
                t[ind+1].value[rn++] = t[ind].value[i];
    }
    build(l,mid,ind + 1);
    build(mid + 1,r,ind + 1);
}
//如果左孩子的个数大于k则去左孩子查找，并且更新查询区间为[l+num3,l+num3+num1-1]
//如果左孩子的个数小于k，则去右孩子查找，并且更新查询区间为[mid+1+num4,mid+num2+num4]
LL query(int a,int b,int k,int p,int l,int r)
{
    if(l == r) return t[p].value[a];
    //num1表示[a,b]进入左孩子元素的个数，num2表示[a,b]进入右孩子的个数
    //num3表示[1,a-1]进入左孩子的个数，num4表示[1,a-1]进入右孩子的个数
    //SSS 记录区间[a,b]中小于第k大的元素的值和
    LL sss;
    int num1,num2,num3,num4;
    int mid = (l+r)/2;
    if(a == l)
    {
        num1 = t[p].num[b];
        num3 = 0;
        sss = t[p].sum[b];
    }
    else
    {
        num1 = t[p].num[b] - t[p].num[a-1];
        num3 = t[p].num[a-1];
        sss = t[p].sum[b] - t[p].sum[a-1];
    }
    if(num1 >= k)//进入左孩子，更新查询区间
    {
        a = l + num3;
        b = l + num3 + num1 - 1;
        return query(a,b,k,p+1,l,mid);
    }
    else       //进入右孩子
    {
        tsum += sss;
        num4 = a - l - num3;
        num2 = b - a + 1 - num1;
        a = mid + 1 + num4  ;
        b = mid + 1 + num2 + num4 - 1;
        return query(a,b,k-num1,p+1,mid+1,r);
    }
}
int main()
{
    int n,m;
    int T;
    scanf("%d",&T);
    for(int Case = 1;Case <= T;Case ++)
    {
        memset(ssum,0,sizeof(ssum));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&t[0].value[i]);
            ssum[i] = ssum[i-1] + t[0].value[i];
            sorted[i] = t[0].value[i];
        }
        sort(sorted+1,sorted+n+1);
        build(1,n,0);
        scanf("%d",&m);
        printf("Case #%d:\n",Case);
        for(int i=0;i<m;i++)
        {
            tsum = 0;
            int l,r,q;
            scanf("%d%d",&l,&r);
            l++;r++;
            q = (r-l)/2 + 1;
            LL zz = query(l,r,q,0,1,n);
            LL ans = (q-1)*zz - tsum;
            ans += (ssum[r] - ssum[l-1] - zz - tsum - (r-l+1-q)*zz);
            printf("%lld\n",ans);
        }
        printf("\n");
    }
    return 0;
}
