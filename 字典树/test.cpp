#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<malloc.h>
#include<stdlib.h>

#define ll long long

using namespace std;


char s[15];

ll zz[150];
int main()
{
    for(int i=0;i<95;i++)
        zz[i] = -2;

    int cnty = 0,cntn = 0;

    while(scanf("%s",s)&&s[1]!='N')
    {

        ll zzt=0;
        for(int i=0;i<7;i++){
            if(s[i]<'A'){
                zzt=zzt*16+s[i]-'0';
            }
            else{
                zzt=zzt*16+s[i]-'A'+10;
            }
        }

        ll tmp = (zzt/16)%64;

        if(zz[tmp]==zzt/16)
        {
            cout<<"Hit"<<endl;
            cnty++;
        }
        else
        {
            cntn++;
            zz[tmp] = zzt/16;
            cout<<"Miss"<<endl;
        }
    }

    char c = '%';

    printf("Hit ratio = %.2f%c\n",cnty*1.0/(cnty+cntn)*100.0,c);
}
