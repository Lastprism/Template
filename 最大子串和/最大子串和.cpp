#include<iostream>  
#define MAXSIZE 100  
using namespace std;  
int MaxSum(int[],int);  
int main(void)  
{  
    int n;  
    int array[MAXSIZE];  
    while(cin>>n)  
    {  
        for(int i=1;i<=n;i++)  
        {  
            cin>>array[i];  
        }  
        cout<<MaxSum(array,n)<<endl;  
    }  
    return 0;  
}  
int MaxSum(int array[],int n)  
{  
    int b=0;  
    int sum=0;  
    for(int i=1;i<=n;i++)  
    {  
        if(b>0)  
        {  
            b+=array[i];  
        }  
        else  
        {  
            b=array[i];  
        }  
        if(b>sum)  
        {  
            sum=b;  
        }  
    }  
    return sum;  
}