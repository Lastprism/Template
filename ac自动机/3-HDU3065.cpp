
/*-------------------------------------------------------------------------------------------------------------------
@AC自动机（O( (N+M)*L )）
（1）解决的问题：
给定一堆模式串，给定一个字符串，问每个模式串在该字符串出现的次数
（2）关键思想：
注释
----------------------------------------------------------------------------------------------------------------------*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<malloc.h>
#include<queue>
#define MAX 26          //字典树儿子数量
#define M 2000000+10    //长度
#define LEN 55          //模式串长度
using namespace std;

struct Node
{
    Node* next[MAX];
    int sum;
    Node* fail;
};
//初始化节点 root 一个字典树节点
void init(Node* root)
{
    for(int i=0;i<MAX;i++)
    {
        root->next[i] = NULL;
    }
    root->sum = 0;
    root->fail = NULL;
}
//字典树插入 root字典树根节点 s模式串 id该模式串是第几个模式串
void Insert(Node* root, char *s,int id)
{
    Node* p = root;
    int len = strlen(s);
    for(int i=0;i<len;i++)
    {
        int x = s[i] - 'A';
        if(!p -> next[x])
        {
            Node *tmp = (Node *)malloc(sizeof(Node));
            for(int i=0;i<MAX;i++)
                tmp -> next[i] = NULL;
            tmp -> sum = 0;
            tmp -> fail = NULL;
            p -> next[x] = tmp;
        }
        p = p -> next[x];
    }
    p -> sum = id;
}
//建立fail指针 root是字典树根节点
void BuildFailPointer(Node* root)
{
    queue<Node*> q;
    Node* temp = root;
    q.push(temp);
    Node* p;
    while(!q.empty())
    {
        //cout<<"11"<<endl;
        temp = q.front();
        q.pop();
        for(int i = 0;i< MAX;i++)
        {
            if(temp -> next[i])
            {
                if(temp == root)
                    temp -> next[i] -> fail = root;
                else
                {
                    p = temp -> fail;
                    while(p)
                    {
                        //cout<<p<<endl;
                        if(p -> next[i])
                        {
                            temp -> next[i] -> fail = p -> next[i];
                            break;
                        }
                        p = p-> fail;
                    }
                    if(p == NULL)
                        temp -> next[i] -> fail = root;
                }
                q.push(temp -> next[i]);
            }
        }
    }
}
//自动机匹配 root字典树根节点 s要匹配的字符串 cnt数组记录第i个模式串出现次数
void AC_Automation(Node* root, char *s,int cnt[])
{
    Node* p = root;
    int len = strlen(s);
    for(int i=0;i<len;i++)
    {
        int x = s[i] -'A';
        if(x<0||x>25)
        {
            p = root;
            continue;
        }
        while(p != root && !p -> next[x]) p = p -> fail;
        p = p -> next[x];
        if(!p) p = root;
        Node* temp = p;
        while(temp != root)
        {
            if(temp -> sum >= 0)
            {
                //cout<<temp -> sum<<endl;
                cnt[temp->sum]++;
            }
            else
                break;
            temp = temp -> fail;
        }
    }
}
char str[1005][LEN];    //模式串
char s[M];              //带匹配的字符串
int cnt[1005];          //记录次数的数组
int main()
{
    int n;
    while(~scanf("%d",&n)&&getchar())
    {
        Node* root = new Node;
        init(root);
        memset(cnt,0,sizeof (cnt));
        for(int i=1;i<=n;i++)
        {
            gets(str[i]);
            Insert(root,str[i],i);
        }
        gets(s);
        BuildFailPointer(root);
        AC_Automation(root,s,cnt);
        for(int i = 1;i<=n;i++)
        {
            if(cnt[i])
                printf("%s: %d\n",str[i],cnt[i]);
        }
    }
    return 0;
}
