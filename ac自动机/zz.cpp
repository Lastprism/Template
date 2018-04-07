#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
#define N 300
#define M 10050
char s[N],str[M];
int a[M],t;
struct Node
{
    struct Node *next[128];
    struct Node *fail;
    int num,flag;
    void init()
    {
        for(int i=0; i<128; i++)
            next[i]=NULL;
        fail=NULL;
        num=0;
        flag=0;
    }
}*root;
void Insert(int id)
{
    Node *p=root;
    int len=strlen(s);
    for(int i=0; i<len; i++)
    {
        int pos=s[i];
        if(p->next[pos]==NULL)
        {
            p->next[pos]=new Node;
            p->next[pos]->init();
        }
        p=p->next[pos];
    }
    p->num=id;
}
void getfail()
{
    Node *p=root,*now,*son;
    queue<Node *>que;
    que.push(p);
    while(!que.empty())
    {
        now=que.front();
        que.pop();
        for(int i=0; i<128; i++)
        {
            son=now->next[i];
            if(son!=NULL)
            {
                if(now==root) son->fail=root;
                else
                {
                    p=now->fail;
                    while(p)
                    {
                        if(p->next[i])
                        {
                            son->fail=p->next[i];
                            break;
                        }
                        p=p->fail;
                    }
                    if(!p) son->fail=root;
                }
                que.push(son);
            }
        }
    }
}
void query(int id)
{
    Node *p=root,*temp;
    int len=strlen(str);
    for(int i=0; i<len; i++)
    {
        int pos=str[i];
        while(!p->next[pos]&&p!=root) p=p->fail;
        p=p->next[pos];
        if(!p) p=root;
        temp=p;
        while(temp!=root)
        {
            if(t>=3) break;
            if(temp->num>0&&temp->flag!=id)
            {
                a[t++]=temp->num;
                temp->flag=id;
            }
            else break;
            temp=temp->fail;
        }
        if(t>=3) break;
    }
}
int main()
{
    int n,m;
    while(~scanf("%d",&n))
    {
        root=new Node;
        root->init();
        getchar();
        for(int i=1; i<=n; i++)
        {
            gets(s);
            Insert(i);
        }
        getfail();
        scanf("%d",&m);
        int ans=0;
        getchar();
        for(int k=1; k<=m; k++)
        {
            t=0;
            gets(str);
            query(k);
            if(t>0)
            {
                ans++;
                sort(a,a+t);
                printf("web %d: ",k);
                for(int i=0; i<t-1; i++)
                    printf("%d ",a[i]);
                printf("%d\n",a[t-1]);
            }
        }
        printf("total: %d\n",ans);
    }
    return 0;
}
