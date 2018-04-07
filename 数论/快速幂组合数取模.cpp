#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod = 1000000007LL;

const int MAX_N = 100010;

//快速幂
ll modPow(ll a, ll p) {
    if(p == 0) {
        return 1;
    }
    ll res = modPow(a, p/2);
    res = (res * res) % mod;
    if(p % 2) {
        res = (res * a) % mod;
    }
    return res;
}

//求逆元
ll modInverse(ll a) {
    return modPow(a, mod-2);
}

ll fac[MAX_N];
ll facInv[MAX_N];

//求阶乘
void calcFac() {
    fac[0] = 1;
    facInv[0] = 1;
    for(int i = 1;i<MAX_N;++i) {
        fac[i] = (i * fac[i-1]) % mod;
        facInv[i] = modInverse(fac[i]);
    }
}
//求n!/r!
ll perm(int n, int r) {
    return (fac[n] * facInv[r]) % mod;
}
//求n!/r!*(n-r)!
ll C(int n, int r) {
    return (((fac[n] * facInv[r]) % mod) * facInv[n-r]) % mod;
}

int main() {
    ios::sync_with_stdio(false);

    calcFac();

    map<int, int> a;

    int n;
    cin>>n;

    for(int i = 0;i<n;++i) {
        int x;
        cin>>x;
        a[x]++;
    }

    ll res = 1;

    int maxCnt = 0;
    int x = 0;
    for(auto it = a.begin();it != a.end();++it) {
        if(it->second > maxCnt) {
        	maxCnt = it->second;
        	x = it->first;
        }
    }

    for(auto it = a.begin();it != a.end();++it) {
        if(it->first != x) {
	        res = (res * perm(maxCnt, maxCnt - it->second)) % mod;
        }
    }

    cout<<res<<endl;
    return 0;
}
