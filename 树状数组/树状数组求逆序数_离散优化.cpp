#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 500010
#define lowbit(x)  ( (x)&(-(x)) )

struct Node{ int data, pos; };

int n;
int count[N], p[N];
Node d[N];

int cmp( const void* a, const void* b )
{
    Node* ta= (Node*)a;
    Node* tb= (Node*)b;

    return ta->data- tb->data;
}

void  update( int pos, int value )
{
    int x= pos;
    while( x<= n )
    {
        count[x]+= value;
        x+= lowbit(x);
    }
}

int  getsum( int pos )
{
    int x= pos, sum= 0;
    while( x )
    {
        sum+= count[x];
        x-= lowbit(x);
    }

    return sum;
}

int main()
{
    while( scanf("%d",&n)!= EOF )
    {
        if( n== 0 ) break;

        for( int i= 1; i<= n; ++i )
        {
            scanf("%d", &d[i].data );
            d[i].pos= i;
        }

        qsort( d+ 1, n, sizeof(d[0]), cmp );

        int id= 1; p[ d[1].pos ]= 1;

        for( int i= 2; i<= n; ++i )
        if( d[i].data== d[i-1].data ) p[ d[i].pos ]= id;
        else                          p[ d[i].pos ]= ++id;

        memset( count, 0, sizeof(count) );

        __int64 ans= 0;
        for( int i= 1; i<= n; ++i )
        {
            update( p[i], 1 );
            ans+= (__int64)( i- getsum( p[i] ) );
        }

        printf("%I64d\n", ans );
    }

    return 0;
}
