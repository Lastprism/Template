//HDU3068
/*-------------------------------------------------------------------------------------------------------------------
@manacher（O（N））
求字符串中最长回文子串
----------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define MIN(x,y) x<y?x:y
#define MAX(x,y) x>y?x:y
const int maxn = 110000+10;

char s[maxn<<2];
char str[maxn<<2];
int p[maxn<<2];
//初始化，在字符串开头加一个$在两个字符之间加#
//s原串 str初始化后的串
void init(char *s,char *str)
{
	str[0] = '$';
	str[1] = '#';
	int cnt = 2;
	int slen = strlen(s);
	for(int i=0;i<slen;i++)
	{
		str[cnt++] = s[i];
		str[cnt++] = '#';
	}
	str[cnt] = '\0';
}
//manacher一下，返回最长回文子串的长度
//p[i]用来记录以第i个字符为中心的最长回文半径
int pk(int *p,char *str)
{
    int i;
    int mx = 0;
    int id = 0;
    int n = strlen(str);
    for(i=1; i<n; i++)
    {
    	p[i]=mx>i?MIN(p[2*id-i],mx-i):1;
    	while(str[i+p[i]] == str[i-p[i]])
    		p[i]++;
        if( p[i] + i > mx )
        {
            mx = p[i] + i;
            id = i;
        }
    }
    int ans = 0;
    for(int i=0;i<n;i++)
    	ans = MAX(ans,p[i]);
    return ans - 1;
}
int main()
{
	while(~scanf("%s",s))
	{
		memset(p,0,sizeof(p));
		init(s,str);
		printf("%d\n",pk(p,str));
	}
	return 0;
}
