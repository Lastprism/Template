
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define LL long long
#define G  1100000
#define mod 1000003
LL pri[G];
LL ni[G],ans;
LL pow(LL a,int b)
{
    LL ans=1,base=a;
    while (b>0)
    {
        if (b%2==1)
            ans=(base*ans)%mod;
        base=(base*base)%mod;
        b/=2;
    }
    return ans;
}
void s()   //打表
{
    pri[0]=1;
    ni[0]=1;
    for (int i=1;i<G ;i++)
    {
        pri[i]=pri[i-1]*i%mod;  //N！
        ni[i]=pow(pri[i],mod-2);
    }
}
int main()
{
    s();
    int t,n,m,k=1;
	scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d",&n,&m);
        ans=((pri[n]*ni[m]%mod)*ni[n-m])%mod; // C（n，m）= n！/（m！*（n-m）！）
        printf("Case %d: %lld\n",k++,ans);
    }
    return 0;
}

