#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#define N 100050
using namespace std;

int sorted[N];   //�����������
int toleft[30][N]; //toleft[i][j]��ʾ��i���1��k�ж��ٸ����������
int tree[30][N];  //��ʾÿ��ÿ��λ�õ�ֵ
int n;//��������ĸ���
long long sum[N];//���������ǰλ�ü�֮ǰ������Ԫ��֮��
long long lsum[30][N];//��deep�� ��i��Ԫ���ڵ������� ��iǰ�汻���ֵ���������Ԫ��֮��
long long tsum;//��ʾС����λ��ave���ֵĺ�

void building(int l,int r,int dep)
{
    if(l==r) return;
    int mid = (l+r)>>1;
    int temp = sorted[mid];
    int i,sum_same=mid-l+1;//��ʾ�����м�ֵ���ұ�������ߵĸ���
    for(i=l; i<=r; i++)
        if(tree[dep][i]<temp)
            sum_same--;
    int leftpos = l;
    int rightpos = mid+1;
    for(i=l; i<=r; i++)
    {
        if(tree[dep][i]<temp)//���м����С���������
        {
            tree[dep+1][leftpos++]=tree[dep][i];
            lsum[dep][i] = lsum[dep][i-1] + tree[dep][i];//��¼�����ֵ���ߵĺ��Ƕ���
        }
        else if(tree[dep][i]==temp&&sum_same>0)//�����м����ֵ��������ߣ�ֱ��sum==0��ֵ��ұ�
        {
            tree[dep+1][leftpos++]=tree[dep][i];
            lsum[dep][i] = lsum[dep][i-1] + tree[dep][i];
            sum_same--;
        }
        else //�ұ�
        {
            tree[dep+1][rightpos++]=tree[dep][i];
            lsum[dep][i] = lsum[dep][i-1];
        }
        toleft[dep][i] = toleft[dep][l-1] + leftpos - l;   //��1��i����ߵĸ���
    }
    building(l,mid,dep+1);
    building(mid+1,r,dep+1);
}

//��ѯ�����k�������[L,R]�Ǵ����䣬[l,r]��Ҫ��ѯ��С����
int query(int L,int R,int l,int r,int dep,int k)
{
    //cout<<L<<" "<<R<<" "<<endl;
    if(l==r) return tree[dep][l];
    int mid = (L+R)>>1;
    int cnt = toleft[dep][r] - toleft[dep][l-1]; //[l,r]��λ����ߵĸ���
    if(cnt>=k)
    {
        int newl = L + toleft[dep][l-1] - toleft[dep][L-1]; //L+Ҫ��ѯ������ǰ��������ߵĸ���
        int newr = newl + cnt - 1;  //��˵���ϲ�ѯ����ᱻ������ߵĸ���
        return query(L,mid,newl,newr,dep+1,k);
    }
    else
    {
        int newr = r + (toleft[dep][R] - toleft[dep][r]);
        int newl = newr - (r-l-cnt);
        tsum+=lsum[dep][r]-lsum[dep][l-1];//����
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
            sum[i] = sum[i-1]+sorted[i];//���������ǰλ�ü�֮ǰ������Ԫ��֮��
            tree[0][i]=sorted[i] ;
        }
        sort(sorted+1,sorted+1+n);
        building(1,n,0);
        int l,r;
        int m;//��ѯ����
        scanf("%d",&m);
        printf("Case #%d:\n",cas++);
        while(m--)
        {
            scanf("%d%d",&l,&r);
            l++,r++;
            tsum=0;//��ʾС����λ��ave���ֵĺ�
            int k=(r-l)/2+1;//k������ab����λ��
            long long ave= query(1,n,l,r,0,k);//ave����λ����ֵ��r-l+1-k��������ĸ���
            long long ans=sum[r]-sum[l-1]-ave*(r-l+1-k)-tsum-ave;//��λ���ұߺͣ�����ave�Ĳ���
            ans+=(k-1)*ave-tsum;//��λ����ߺͣ�С��ave�Ĳ���
            printf("%lld\n",ans);
        }
        printf("\n");
    }
    return 0;
}
