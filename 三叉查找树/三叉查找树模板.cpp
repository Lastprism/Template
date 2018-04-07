#include<iostream>
#include<cstdio>

using namespace std;

typedef struct tnode *Tptr;
typedef struct tnode {
    char s;
    Tptr lokid, eqkid, hikid;
} Tnode;
int search(char *s) // s是想要查找的字符串
{
    Tptr p;
    p = t; //t 是已经构造好的Ternary search tree 的root 节点.
    while (p) {
        if (*s < p->s) { // 如果*s 比 p->s 小, 那么节点跳到p->lokid
            p = p->lokid;
        } else if (*s > p->s) {
            p = p->hikid;
        } else {
            if (*(s) == '\0') { //当*s 是'\0'时候,则查找成功
                return 1;
            } //如果*s == p->s,走向中间节点,并且s++
            s++;
            p = p->eqkid;
        }
    }
    return 0;
}
Tptr insert(Tptr p, char *s)
{
    if (p == NULL) {
        p = (Tptr)malloc(sizeof(Tnode));
        p->s = *s;
        p->lokid = p->eqkid = p->hikid = NULL;
    }
    if (*s < p->s) {
        p->lokid = insert(p->lokid, s);
    } else if (*s > p->s) {
        p->hikid = insert(p->hikid, s);
    } else {
        if (*s != '\0') {
            p->eqkid = insert(p->eqkid, ++s);
        } else {
            p->eqkid = (Tptr) insertstr; //insertstr 是要插入的字符串,方便遍历所有字符串等操作
        }
    }
    return p;
}
//这里以字典序输出所有的字符串
void traverse(Tptr p) //这里遍历某一个节点以下的所有节点,如果是非根节点,则是有同一个前缀的字符串
{
    if (!p) return;
    traverse(p->lokid);
    if (p->s != '\0') {
        traverse(p->eqkid);
    } else {
        printf("%s\n", (char *)p->eqkid);
    }
    traverse(p->hikid);
}
int main()
{
    return 0;
}
