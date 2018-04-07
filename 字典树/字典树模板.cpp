
/*-------------------------------------------------------------------------------------------------------------------
@字典树（时间复杂度）
给定一堆字符串，查询某个字符串是否出现过
----------------------------------------------------------------------------------------------------------------------*/
#include <iostream>
#include<cstdlib>
#define MAX 26
using namespace std;

typedef struct TrieNode                     //Trie结点声明
{
    bool isStr;                            //标记该结点处是否构成单词
    struct TrieNode *next[MAX];            //儿子分支
}Trie;

void insert(Trie *root,const char *s)     //将单词s插入到字典树中
{
    if(root==NULL||*s=='\0')
        return;
    int i;
    Trie *p=root;
    while(*s!='\0')
    {
        if(p->next[*s-'a']==NULL)        //如果不存在，则建立结点
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
    p->isStr=true;                       //单词结束的地方标记此处可以构成一个单词
}

int search(Trie *root,const char *s)  //查找某个单词是否已经存在
{
    Trie *p=root;
    while(p!=NULL&&*s!='\0')
    {
        p=p->next[*s-'a'];
        s++;
    }
    return (p!=NULL&&p->isStr==true);      //在单词结束处的标记为true时，单词才存在
}

void del(Trie *root)                      //释放整个字典树占的堆区空间
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
    int v;   //根据需要变化
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
            q->v = 1;    //初始v==1
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
    p->v = -1;   //若为结尾，则将v改成-1表示
}
int findTrie(char *str)
{
    int len = strlen(str);
    Trie *p = root;
    for(int i=0; i<len; ++i)
    {
        int id = str[i]-'0';
        p = p->next[id];
        if(p == NULL)   //若为空集，表示不存以此为前缀的串
            return 0;
        if(p->v == -1)   //字符集中已有串是此串的前缀
            return -1;
    }
    return -1;   //此串是字符集中某串的前缀
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
