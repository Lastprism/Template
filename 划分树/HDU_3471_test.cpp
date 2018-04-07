#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#define N 100050
using namespace std;

int sorted[N];   //排序完的数组
int toleft[30][N]; //toleft[i][j]表示第i层从1到k有多少个数分入左边
int tree[30][N];  //表示每层每个位置的值
int n;//输入的数的个数
long long sum[N];//保存包括当前位置及之前的所有元素之和
long long lsum[30][N];//在deep层 第i个元素在的区间中 在i前面被划分到左子树的元素之和
long long tsum;//表示小于中位数ave部分的和

void building(int l,int r,int dep)
{
    if(l==r) return;
    int mid = (l+r)>>1;
    int temp = sorted[mid];
    int i,sum_same=mid-l+1;//表示等于中间值而且被分入左边的个数
    for(i=l; i<=r; i++)
        if(tree[dep][i]<temp)
            sum_same--;
    int leftpos = l;
    int rightpos = mid+1;
    for(i=l; i<=r; i++)
    {
        if(tree[dep][i]<temp)//比中间的数小，分入左边
        {
            tree[dep+1][leftpos++]=tree[dep][i];
            lsum[dep][i] = lsum[dep][i-1] + tree[dep][i];//记录被划分到左边的和是多少
        }
        else if(tree[dep][i]==temp&&sum_same>0)//等于中间的数值，分入左边，直到sum==0后分到右边
        {
            tree[dep+1][leftpos++]=tree[dep][i];
            lsum[dep][i] = lsum[dep][i-1] + tree[dep][i];
            sum_same--;
        }
        else //右边
        {
            tree[dep+1][rightpos++]=tree[dep][i];
            lsum[dep][i] = lsum[dep][i-1];
        }
        toleft[dep][i] = toleft[dep][l-1] + leftpos - l;   //从1到i放左边的个数
    }
    building(l,mid,dep+1);
    building(mid+1,r,dep+1);
}

//查询区间第k大的数，[L,R]是大区间，[l,r]是要查询的小区间
int query(int L,int R,int l,int r,int dep,int k)
{
    //cout<<L<<" "<<R<<" "<<endl;
    if(l==r) return tree[dep][l];
    int mid = (L+R)>>1;
    int cnt = toleft[dep][r] - toleft[dep][l-1]; //[l,r]中位于左边的个数
    if(cnt>=k)
    {
        int newl = L + toleft[dep][l-1] - toleft[dep][L-1]; //L+要查询的区间前被放在左边的个数
        int newr = newl + cnt - 1;  //左端点加上查询区间会被放在左边的个数
        return query(L,mid,newl,newr,dep+1,k);
    }
    else
    {
        int newr = r + (toleft[dep][R] - toleft[dep][r]);
        int newl = newr - (r-l-cnt);
        tsum+=lsum[dep][r]-lsum[dep][l-1];//区间
        return query(mid+1,R,newl,newr,dep+1,k-cnt);
    }
}

int main()
{
    int t,cas=1;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        int i;
        for(i=1; i<=n; i++)
        {
            scanf("%lld",&sorted[i]);
            sum[i] = sum[i-1]+sorted[i];//保存包括当前位置及之前的所有元素之和
            tree[0][i]=sorted[i] ;
        }
        sort(sorted+1,sorted+1+n);
        building(1,n,0);
        int l,r;
        int m;//查询次数
        scanf("%d",&m);
        printf("Case #%d:\n",cas++);
        while(m--)
        {
            scanf("%d%d",&l,&r);
            l++,r++;
            tsum=0;//表示小于中位数ave部分的和
            int k=(r-l)/2+1;//k是区间ab的中位数
            long long ave= query(1,n,l,r,0,k);//ave是中位数的值，r-l+1-k是左边数的个数
            long long ans=sum[r]-sum[l-1]-ave*(r-l+1-k)-tsum-ave;//中位数右边和，大于ave的部分
            ans+=(k-1)*ave-tsum;//中位数左边和，小于ave的部分
            printf("%lld\n",ans);
        }
        printf("\n");
    }
    return 0;
}
