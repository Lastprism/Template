// WTNumber.h: interface for the CWTNumber class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WTNUMBER_H__92E62B40_491A_4A75_AB89_FFB160DB2343__INCLUDED_)
#define AFX_WTNUMBER_H__92E62B40_491A_4A75_AB89_FFB160DB2343__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define INT_BIT_MAX 255
#define FLOAT_BIT_MAX 255

class CWTNumber
{
private:
    int intbits;                     /* ������λ*/
    int floatbits;                   /* С����Ч��λ*/
    char infinite;                   /* �����*/
    char sign;                       /* ����*/
    char intpart[INT_BIT_MAX];       /* ��������*/
    char floatpart[FLOAT_BIT_MAX];   /* С������*/
private:
    char* m_sz;
public:
    /* ��������ָ������.*/
    typedef void (*PFNCALC)(const CWTNumber&,const CWTNumber&,CWTNumber&);
    CWTNumber();
    CWTNumber(const char* szNum);
    ~CWTNumber();
    /* ת�����ַ���*/
    char* ToString();
    void FreeString();
    /* ��ʼ��WTNumberΪ0.*/
    void InitWTNumberToZero();
    /* �ж���Ҫ���ٸ��ַ��ռ�洢WTNumberת�����ַ���.*/
    int StrLenByWTNumber();
    /* ���ַ���ת����WTNumber.*/
    void StrToWTNumber(const char *arr);
    /* ��WTNumberת�����ַ���.*/
    void WTNumberToStr(char *szBuf);
    /* ������λ,ɾ���������λ��0�ĺ����С��λ��0����λ.*/
    void AdjustBits();
    /* �ƶ�С����,delta=0���ƶ�,delta<0�����ƶ�,delta>0�����ƶ�.*/
    void MoveFloatPoint(int delta);
    /* ʹ����� */
    void MakeInfinite();
    /* �Ƚ�2������С */
    int WTCompare(const CWTNumber& n) const;
    /* �ж��Ƿ�Ϊ0 */
    int IsZero() const;
    /* ��ֵ������*/
    CWTNumber& operator=(const CWTNumber& n);

    /* ��������� */
    CWTNumber operator+(const CWTNumber& n);
    CWTNumber operator-(const CWTNumber& n);
    CWTNumber operator*(const CWTNumber& n);
    CWTNumber operator/(const CWTNumber& n);
    CWTNumber& operator+=(const CWTNumber& n);
    CWTNumber& operator-=(const CWTNumber& n);
    CWTNumber& operator*=(const CWTNumber& n);
    CWTNumber& operator/=(const CWTNumber& n);

    bool operator>(const CWTNumber& n);
    bool operator>=(const CWTNumber& n);
    bool operator<(const CWTNumber& n);
    bool operator<=(const CWTNumber& n);
    bool operator==(const CWTNumber& n);
    bool operator!=(const CWTNumber& n);
    /* �ӷ�*/
    static void WTAdd(const CWTNumber& n1,const CWTNumber& n2,CWTNumber& Res);
    /* �˷�*/
    static void WTMultiply(const CWTNumber& n1,const CWTNumber& n2,CWTNumber& Res);
    /* ����*/
    static void WTSubtract(const CWTNumber& n1,const CWTNumber& n2,CWTNumber& Res);
    /* ����*/
    static void WTDivide(const CWTNumber& n1,const CWTNumber& n2,CWTNumber& Res);
    /* ���������������ؽ�� */
    static char *Result(const char *val1,const char *val2,PFNCALC pfnCalc);
};


#endif // !defined(AFX_WTNUMBER_H__92E62B40_491A_4A75_AB89_FFB160DB2343__INCLUDED_)



// WTNumber.cpp: implementation of the CWTNumber class.
//
//////////////////////////////////////////////////////////////////////
#include <string.h>
#include <stdlib.h>
#include "WTNumber.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWTNumber::CWTNumber()
{
    InitWTNumberToZero();
}
CWTNumber::CWTNumber(const char* szNum)
{
    InitWTNumberToZero();
    StrToWTNumber(szNum);
}
CWTNumber::~CWTNumber()
{
    FreeString();
}
void CWTNumber::FreeString()
{
    if(m_sz) delete []m_sz;
    m_sz=NULL;
}
void CWTNumber::InitWTNumberToZero()
{
    memset(this,0,sizeof(CWTNumber));
}
int CWTNumber::StrLenByWTNumber()
{
    int len = floatbits+intbits+1;
    if(intbits==0) len++;    /* .1 --> 0.1*/
    if(floatbits) len++;    /* '.'*/
    if(sign) len++;        /* '-'*/
    if(infinite) return 11;    /* #INFINITE */
    return len;
}
void CWTNumber::StrToWTNumber(const char *arr)
{
    char *point;
    InitWTNumberToZero();
    if(*arr=='-')    /* ����Ǹ���*/
    {
        arr++;
        sign=1;
    }
    point=strchr(arr,'.');
    if(point)    /* �ҵ�С���� */
    {
        int n=intbits=point-arr;    /* �����������λ */
        while(n)    /* ������λ��==0��ѭ�� */
        {
            intpart[intbits-n]=arr[n-1]-'0';    /* �����ֵ�λ���ڵ��±�Ԫ��*/
            n--;
        }
        while(*++point)
        {
            floatpart[floatbits]=*point-'0';
            floatbits++;
        }
    }
    else    /* ˵��ûдС����,ȫ������.*/
    {
        int n=intbits=strlen(arr);
        while(n)
        {
            intpart[intbits-n]=arr[n-1]-'0';
            n--;
        }
    }
    AdjustBits();
    /* ����-0 ��0�����*/
    if(floatbits==0)
    {
        if(intbits==0 || intbits==1&&intpart[0]==0)
            sign=0;
    }
}

void CWTNumber::WTNumberToStr(char *szBuf)
{
    int n=intbits,c;
    memset(szBuf,0,StrLenByWTNumber());
    if(sign)    /* ����Ǹ���*/
    {
        *szBuf++='-';
    }
    if(infinite)
    {
        strcat(szBuf,"#INFINITE");
        return;
    }
    while(n)
    {
        szBuf[intbits-n]=intpart[n-1]+'0';
        n--;
    }
    c=0;    /* �Ƿ����0*/
    if(intbits==0) {
        strcat(szBuf,"0");
        c=1;
    }
    if(floatbits) strcat(szBuf,".");
    n=0;
    while(n<floatbits)
    {
        szBuf[intbits+1+n+c]=floatpart[n]+'0';
        n++;
    }
}
void CWTNumber::AdjustBits()
{
    while(intbits>1&&intpart[intbits-1]==0) intbits--;
    while(floatbits&&floatpart[floatbits-1]==0) floatbits--;
}
void CWTNumber::MoveFloatPoint(int delta)
{
    /* delta<0�������ƶ�С����,delta>0�������ƶ�С���� */
    if(delta)
    {
        CWTNumber n=*this;
        InitWTNumberToZero();
        sign=n.sign;
        if(delta<0)
        {
            int i;
            delta=-delta;
            for(i=delta;i<n.intbits;i++)
            {
                intpart[intbits++]=n.intpart[i];
            }
            for(i=delta-1;i>=0;i--)
            {
                floatpart[floatbits++]=n.intpart[i];
            }
            for(i=0;i<n.floatbits;i++)
            {
                floatpart[floatbits++]=n.floatpart[i];
            }
        }
        else
        {
            int i;
            for(i=delta;i<n.floatbits;i++)    /* ����С������*/
            {
                floatpart[floatbits++]=n.floatpart[i];
            }
            for(i=delta-1;i>=0;i--)    /* С���������Ĳ���*/
            {
                intpart[intbits++]=n.floatpart[i];
            }
            for(i=0;i<n.intbits;i++)    /* ��������*/
            {
                intpart[intbits++]=n.intpart[i];
            }
        }
    }
    AdjustBits();
}
void CWTNumber::MakeInfinite()
{
    infinite=1;
}

int CWTNumber::WTCompare(const CWTNumber& n) const
{
    /* �����ǱȽϷ���*/
    if(sign==0&&n.sign!=0)    /* pn1������,pn2�Ǹ���*/
        return 1;    /* >*/
    else if(sign!=0&&n.sign==0)    /* pn1�Ǹ���,pn2������*/
        return -1;    /* <*/
    else    /* ͬ��״̬*/
    {
        /* �Ƚ���������*/
        if(intbits>n.intbits)    /* pn1������λ��*/
            return sign?-1:1;
        else if(intbits<n.intbits)
            return sign?1:-1;
        else    /* ������λ��ͬ*/
        {
            int i=intbits-1;    /*ָ�����λ*/
            while(i>=0)
            {
                if(intpart[i]>n.intpart[i])
                    return sign?-1:1;
                else if(intpart[i]<n.intpart[i])
                    return sign?1:-1;
                else i--;
            }
            /* ����������ͬ,�Ƚ�С������*/
            for(i=0;i<floatbits&&i<n.floatbits;)
            {
                if(floatpart[i]>n.floatpart[i])
                    return sign?-1:1;
                else if(floatpart[i]<n.floatpart[i])
                    return sign?1:-1;
                else i++;
            }
            if(i<floatbits) return sign?-1:1;
            if(i<n.floatbits) return sign?1:-1;
            return 0;    /* ���*/
        }
    }
}
int CWTNumber::IsZero() const
{
    if(floatbits==0&&intbits==0) return 1;
    if(floatbits==0&&intbits==1&&intpart[0]==0) return 1;
    return 0;
}

void CWTNumber::WTAdd(const CWTNumber& n1,const CWTNumber& n2,CWTNumber& Res)
{
    Res.InitWTNumberToZero();
    if(n1.sign^n2.sign)    /*���*/
    {
        CWTNumber rn2=n2;
        rn2.sign=n1.sign;
        WTSubtract(n1,rn2,Res);
    }
    else    /*ͬ��*/
    {
        int maxfloatbits=n1.floatbits>n2.floatbits?n1.floatbits:n2.floatbits;
        int addbit=0;    /* ��λֵ*/
        int i,j;
        for(i=maxfloatbits-1;i>=0;i--)
        {
            int value=n1.floatpart[i]+n2.floatpart[i]+addbit;
            addbit=value/10;    /* �����Ƿ񳬹�10. ���ý�λֵ*/
            Res.floatpart[i]=value%10;
        }
        Res.floatbits=maxfloatbits;
        /* ����,С�����ּ������.*/
        for(j=0;j<n1.intbits||j<n2.intbits;j++)
        {
            int value=n1.intpart[j]+n2.intpart[j]+addbit;
            addbit=value/10;
            Res.intpart[j]=value%10;
            Res.intbits++;
        }
        if(addbit>0)
        {
            Res.intpart[j]=addbit;
            Res.intbits++;
        }
        Res.sign=n1.sign;    /*��������*/
        Res.AdjustBits();
    }
}

void CWTNumber::WTMultiply(const CWTNumber& n1,const CWTNumber& n2,CWTNumber& Res)
{
    CWTNumber z1=n1,z2=n2;
    CWTNumber sum;
    int i,j;
    sum.InitWTNumberToZero();
    Res.InitWTNumberToZero();
    z1.MoveFloatPoint(z1.floatbits);
    z2.MoveFloatPoint(z2.floatbits);
    /* ����z1*z2 */
    for(i=0;i<z2.intbits;i++)
    {
        CWTNumber tmp;    /* �����ʱ�˻�*/
        int addbit=0;
        tmp.intbits=z1.intbits+i;
        for(j=0;j<z1.intbits;j++)
        {
            int value = z2.intpart[i]*z1.intpart[j]+addbit;
            addbit=value/10;
            tmp.intpart[j+i]=value%10;
        }
        if(addbit)
        {
            tmp.intpart[j+i]=addbit;
            tmp.intbits++;
        }
        WTAdd(sum,tmp,Res);
        sum=Res;
    }
    Res=sum;
    Res.MoveFloatPoint(-(n1.floatbits+n2.floatbits));
    /* �жϷ���,���Ϊ��*/
    if(n1.sign^n2.sign) Res.sign=1;
}

void CWTNumber::WTSubtract(const CWTNumber& n1,const CWTNumber& n2,CWTNumber& Res)
{
    Res.InitWTNumberToZero();
    if(n1.sign^n2.sign)    /* ������*/
    {
        CWTNumber rn2=n2;
        rn2.sign=n1.sign;
        WTAdd(n1,rn2,Res);
    }
    else    /* ͬ�����*/
    {
        int cmp=n1.WTCompare(n2);
        int swapflag,i,maxfloatbits,subtractbit;
        if(cmp==0) return;    /* ��Ⱦ�û��Ҫ�ټ���.*/
        swapflag=n1.sign==0?cmp==-1:cmp==1;
        const CWTNumber* pn1=&n1;
        const CWTNumber* pn2=&n2;
        if(swapflag)
        {
            const CWTNumber *t=pn1;
            pn1=pn2;
            pn2=t;
        }
        maxfloatbits=pn1->floatbits>pn2->floatbits?pn1->floatbits:pn2->floatbits;
        subtractbit=0;    /* ��λֵ*/
        /* �ȼ���С������*/
        for(i=maxfloatbits-1;i>=0;i--)
        {
            if(pn1->floatpart[i]-subtractbit<pn2->floatpart[i])
            {
                int value=pn1->floatpart[i]-pn2->floatpart[i]-subtractbit+10;
                subtractbit=1;
                Res.floatpart[i]=value;
            }
            else
            {
                int value=pn1->floatpart[i]-pn2->floatpart[i]-subtractbit;
                subtractbit=0;
                Res.floatpart[i]=value;
            }
        }
        Res.floatbits=maxfloatbits;
        /* ����С�����ּ������.*/
        for(i=0;i<pn1->intbits||i<pn2->intbits;i++)
        {
            if(pn1->intpart[i]-subtractbit<pn2->intpart[i])
            {
                int value=pn1->intpart[i]-pn2->intpart[i]-subtractbit+10;
                subtractbit=1;
                Res.intpart[i]=value;
            }
            else
            {
                int value=pn1->intpart[i]-pn2->intpart[i]-subtractbit;
                subtractbit=0;
                Res.intpart[i]=value;
            }
            Res.intbits++;
        }
        Res.sign=swapflag?!n1.sign:n1.sign;    /*��������*/
        Res.AdjustBits();
    }
}
void CWTNumber::WTDivide(const CWTNumber& n1,const CWTNumber& n2,CWTNumber& Res)
{
    CWTNumber z1=n1,z2=n2;
    int deta=z2.floatbits-z1.floatbits;
    z1.MoveFloatPoint(z1.floatbits);
    z2.MoveFloatPoint(z2.floatbits);
    Res.InitWTNumberToZero();
    if(n1.IsZero()) return ;
    if(n2.IsZero()) {
        Res.sign=n1.sign;
        Res.MakeInfinite();
        return ;
    }
    z1.sign=z2.sign=0;                /*ͳһ����,���ڱȽϴ�С*/
    while(z1.intbits!=z2.intbits) {    /*ȷ����λ���,�ⲽ�ķѺܶ�ʱ��*/
        if(z1.intbits<z2.intbits) {
            z1.MoveFloatPoint(1);
            deta--;
        } else {
            z2.MoveFloatPoint(1);
            deta++;
        }
    }
    while(Res.floatbits<(INT_BIT_MAX/2)) {
        int cmp=z1.WTCompare(z2);
        int n=10;
        CWTNumber mulres,subres;
        if(cmp==-1) {      /*z1<z2*/
            z1.MoveFloatPoint(1);
            Res.floatpart[Res.floatbits++]=0;
            continue;
        } else if(cmp==0) { /*z1==z2*/
            Res.floatpart[Res.floatbits++]=1;
            break;
        }
        do {    /*����*/
            CWTNumber tmp;
            tmp.intpart[0]=--n;
            tmp.intbits=1;
            WTMultiply(z2,tmp,mulres);
        } while((cmp=mulres.WTCompare(z1))==1);
        Res.floatpart[Res.floatbits++]=n;
        if(cmp==0) break;
        WTSubtract(z1,mulres,subres);
        subres.MoveFloatPoint(1);
        z1=subres;
    }
    Res.MoveFloatPoint(1);
    Res.MoveFloatPoint(deta);
    /* �жϷ���,���Ϊ��*/
    if(n1.sign^n2.sign) Res.sign=1;
}
char *CWTNumber::Result(const char *val1,const char *val2,PFNCALC pfnCalc)
{
    CWTNumber n1,n2,res;
    n1.StrToWTNumber(val1);
    n2.StrToWTNumber(val2);
    pfnCalc(n1,n2,res);
    return res.ToString();
}

char* CWTNumber::ToString()
{
    FreeString();
    m_sz=new char[StrLenByWTNumber()];
    WTNumberToStr(m_sz);
    return m_sz;
}

CWTNumber& CWTNumber::operator=(const CWTNumber& n)
{
    if(this!=&n) {
        FreeString();
        memcpy(this,&n,sizeof(CWTNumber));
        if(n.m_sz)
        {
            m_sz=strdup(n.m_sz);
        }
    }
    return *this;
}


CWTNumber CWTNumber::operator+(const CWTNumber& n)
{
    CWTNumber res;
    CWTNumber::WTAdd(*this,n,res);
    return res;
}
CWTNumber CWTNumber::operator-(const CWTNumber& n)
{
    CWTNumber res;
    CWTNumber::WTSubtract(*this,n,res);
    return res;
}
CWTNumber CWTNumber::operator*(const CWTNumber& n)
{
    CWTNumber res;
    CWTNumber::WTMultiply(*this,n,res);
    return res;
}
CWTNumber CWTNumber::operator/(const CWTNumber& n)
{
    CWTNumber res;
    CWTNumber::WTDivide(*this,n,res);
    return res;
}
CWTNumber& CWTNumber::operator+=(const CWTNumber& n)
{
    CWTNumber n1=*this,n2=n;
    CWTNumber::WTAdd(n1,n2,*this);
    return *this;
}
CWTNumber& CWTNumber::operator-=(const CWTNumber& n)
{
    CWTNumber n1=*this,n2=n;
    CWTNumber::WTSubtract(n1,n2,*this);
    return *this;
}
CWTNumber& CWTNumber::operator*=(const CWTNumber& n)
{
    CWTNumber n1=*this,n2=n;
    CWTNumber::WTMultiply(n1,n2,*this);
    return *this;
}
CWTNumber& CWTNumber::operator/=(const CWTNumber& n)
{
    CWTNumber n1=*this,n2=n;
    CWTNumber::WTDivide(n1,n2,*this);
    return *this;
}
bool CWTNumber::operator>(const CWTNumber& n)
{
    return WTCompare(n)==1;
}
bool CWTNumber::operator>=(const CWTNumber& n)
{
    return WTCompare(n)!=-1;
}
bool CWTNumber::operator<(const CWTNumber& n)
{
    return WTCompare(n)==-1;
}
bool CWTNumber::operator<=(const CWTNumber& n)
{
    return WTCompare(n)!=1;
}
bool CWTNumber::operator==(const CWTNumber& n)
{
    return WTCompare(n)==0;
}
bool CWTNumber::operator!=(const CWTNumber& n)
{
    return WTCompare(n)!=0;
}
