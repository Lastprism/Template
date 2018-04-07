#define MAX_SIZE 100005
int pa[MAX_SIZE];        //�洢����ͼ�ı�

void init()     //��ʼ��	�ú������Ը��ݾ����������ͳ�ʼ����Ҫ������
{
	for(int i = 0; i < MAX_SIZE; i++)
	{
		pa[i] = i;
	}
}

int findset(int a)	//����·��ѹ��
{
	while(pa[a] != a)
	{
		a = pa[a];
	}
	return a;
}

void union_nodes(int a, int b)      //���Ϻϲ�
{
	int a1 = findset(a);
	int b1 = findset(b);
	if(a1 != b1)		//����ж�������ѡ����Ҫ��Ϊ�˷�ֹfindset·��ѹ����ʱ�������ѭ��
	{
		pa[a1] = b1;		//������������ͼ����������ʱ������Ԫ�ص�˳�����Ҫ�����ܺ��ԣ���ô����Ӧ����"pa[a] = b;"
	}
}





int findset(int v)      //��Ԫ�����ڼ��ϵĴ���Ԫ(��Ϊ����·��ѹ����·��ѹ������ҪĿ����Ϊ�˾����ȷ��Ԫ�����ڵļ��ϣ�
{
	int t1,t2=v;
	while(v!=pa[v])
		v=pa[v];
	while(t2!=pa[t2])        //�����Ż���˼·����·��ѹ������һ�����ڲ��Һ���ִ�еĹ�����ѹ��·������������!
	{
		t1=pa[t2];
		pa[t2]=v;
		t2=t1;
	}
	return v;

}







int findset(int x)
{
	if(pa[x] != x)
	{
		int root = findset(pa[x]);
		return pa[x] = root;
	}
	else
	{
		return x;
	}
}
