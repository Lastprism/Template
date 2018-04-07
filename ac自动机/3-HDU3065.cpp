
/*-------------------------------------------------------------------------------------------------------------------
@AC�Զ�����O( (N+M)*L )��
��1����������⣺
����һ��ģʽ��������һ���ַ�������ÿ��ģʽ���ڸ��ַ������ֵĴ���
��2���ؼ�˼�룺
ע��
----------------------------------------------------------------------------------------------------------------------*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<malloc.h>
#include<queue>
#define MAX 26          //�ֵ�����������
#define M 2000000+10    //����
#define LEN 55          //ģʽ������
using namespace std;

struct Node
{
    Node* next[MAX];
    int sum;
    Node* fail;
};
//��ʼ���ڵ� root һ���ֵ����ڵ�
void init(Node* root)
{
    for(int i=0;i<MAX;i++)
    {
        root->next[i] = NULL;
    }
    root->sum = 0;
    root->fail = NULL;
}
//�ֵ������� root�ֵ������ڵ� sģʽ�� id��ģʽ���ǵڼ���ģʽ��
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
//����failָ�� root���ֵ������ڵ�
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
//�Զ���ƥ�� root�ֵ������ڵ� sҪƥ����ַ��� cnt�����¼��i��ģʽ�����ִ���
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
char str[1005][LEN];    //ģʽ��
char s[M];              //��ƥ����ַ���
int cnt[1005];          //��¼����������
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
