
/*-------------------------------------------------------------------------------------------------------------------
@�ֵ�����ʱ�临�Ӷȣ�
����һ���ַ�������ѯĳ���ַ����Ƿ���ֹ�
----------------------------------------------------------------------------------------------------------------------*/
#include <iostream>
#include<cstdlib>
#define MAX 26
using namespace std;

typedef struct TrieNode                     //Trie�������
{
    bool isStr;                            //��Ǹý�㴦�Ƿ񹹳ɵ���
    struct TrieNode *next[MAX];            //���ӷ�֧
}Trie;

void insert(Trie *root,const char *s)     //������s���뵽�ֵ�����
{
    if(root==NULL||*s=='\0')
        return;
    int i;
    Trie *p=root;
    while(*s!='\0')
    {
        if(p->next[*s-'a']==NULL)        //��������ڣ��������
        {
            Trie *temp=(Trie *)malloc(sizeof(Trie));
            for(i=0;i<MAX;i++)
            {
                temp->next[i]=NULL;
            }
            temp->isStr=false;
            p->next[*s-'a']=temp;
            p=p->next[*s-'a'];
        }
        else
        {
            p=p->next[*s-'a'];
        }
        s++;
    }
    p->isStr=true;                       //���ʽ����ĵط���Ǵ˴����Թ���һ������
}

int search(Trie *root,const char *s)  //����ĳ�������Ƿ��Ѿ�����
{
    Trie *p=root;
    while(p!=NULL&&*s!='\0')
    {
        p=p->next[*s-'a'];
        s++;
    }
    return (p!=NULL&&p->isStr==true);      //�ڵ��ʽ������ı��Ϊtrueʱ�����ʲŴ���
}

void del(Trie *root)                      //�ͷ������ֵ���ռ�Ķ����ռ�
{
    int i;
    for(i=0;i<MAX;i++)
    {
        if(root->next[i]!=NULL)
        {
            del(root->next[i]);
        }
    }
    free(root);
}




//



#define MAX 26
typedef struct Trie
{
    Trie *next[MAX];
    int v;   //������Ҫ�仯
};

Trie *root;
void createTrie(char *str)
{
    int len = strlen(str);
    Trie *p = root, *q;
    for(int i=0; i<len; ++i)
    {
        int id = str[i]-'0';
        if(p->next[id] == NULL)
        {
            q = (Trie *)malloc(sizeof(Trie));
            q->v = 1;    //��ʼv==1
            for(int j=0; j<MAX; ++j)
                q->next[j] = NULL;
            p->next[id] = q;
            p = p->next[id];
        }
        else
        {
            p->next[id]->v++;
            p = p->next[id];
        }
    }
    p->v = -1;   //��Ϊ��β����v�ĳ�-1��ʾ
}
int findTrie(char *str)
{
    int len = strlen(str);
    Trie *p = root;
    for(int i=0; i<len; ++i)
    {
        int id = str[i]-'0';
        p = p->next[id];
        if(p == NULL)   //��Ϊ�ռ�����ʾ�����Դ�Ϊǰ׺�Ĵ�
            return 0;
        if(p->v == -1)   //�ַ��������д��Ǵ˴���ǰ׺
            return -1;
    }
    return -1;   //�˴����ַ�����ĳ����ǰ׺
}
int dealTrie(Trie* T)
{
    int i;
    if(T==NULL)
        return 0;
    for(i=0;i<MAX;i++)
    {
        if(T->next[i]!=NULL)
            deal(T->next[i]);
    }
    free(T);
    return 0;
}
