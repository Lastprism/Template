#define MAX_SIZE 100005
int pa[MAX_SIZE];        //存储有向图的边

void init()     //初始化	该函数可以根据具体情况保存和初始化需要的内容
{
	for(int i = 0; i < MAX_SIZE; i++)
	{
		pa[i] = i;
	}
}

int findset(int a)	//不带路劲压缩
{
	while(pa[a] != a)
	{
		a = pa[a];
	}
	return a;
}

void union_nodes(int a, int b)      //集合合并
{
	int a1 = findset(a);
	int b1 = findset(b);
	if(a1 != b1)		//这个判定条件可选，主要是为了防止findset路径压缩的时候出现死循环
	{
		pa[a1] = b1;		//如果存的是有向图，并且做题时集合中元素的顺序很重要，不能忽略，那么这里应该用"pa[a] = b;"
	}
}





int findset(int v)      //找元素所在集合的代表元(因为用了路径压缩，路径压缩的主要目的是为了尽快的确定元素所在的集合）
{
	int t1,t2=v;
	while(v!=pa[v])
		v=pa[v];
	while(t2!=pa[t2])        //这里优化的思路还是路径压缩（进一步的在查找函数执行的过程中压缩路径），很神奇!
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
