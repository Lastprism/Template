#include<iostream>
#include<cstdio>

using namespace std;

typedef struct tnode *Tptr;
typedef struct tnode {
    char s;
    Tptr lokid, eqkid, hikid;
} Tnode;
int search(char *s) // s����Ҫ���ҵ��ַ���
{
    Tptr p;
    p = t; //t ���Ѿ�����õ�Ternary search tree ��root �ڵ�.
    while (p) {
        if (*s < p->s) { // ���*s �� p->s С, ��ô�ڵ�����p->lokid
            p = p->lokid;
        } else if (*s > p->s) {
            p = p->hikid;
        } else {
            if (*(s) == '\0') { //��*s ��'\0'ʱ��,����ҳɹ�
                return 1;
            } //���*s == p->s,�����м�ڵ�,����s++
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
            p->eqkid = (Tptr) insertstr; //insertstr ��Ҫ������ַ���,������������ַ����Ȳ���
        }
    }
    return p;
}
//�������ֵ���������е��ַ���
void traverse(Tptr p) //�������ĳһ���ڵ����µ����нڵ�,����ǷǸ��ڵ�,������ͬһ��ǰ׺���ַ���
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
