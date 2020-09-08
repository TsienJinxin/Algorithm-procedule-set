#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<iomanip>
using namespace std;
#define MaxSize 100000
void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
void BubbleSort(int a[], int p, int r)
{
	for(int i=p;i<r;i++)
		for (int j = i + 1; j < r + 1; j++)
		{
			if (a[i] > a[j])
				Swap(a[i], a[j]);
		}
}

int Partition(int a[], int p, int r, int x)
{
	int k;
	for (k = p; k <= r; k++)
	{
		if (a[k] == x)
		{
			break;
		}
	}
	Swap(a[p], a[k]);
	int y = a[p];
	int i = p; int j = r + 1;
	while (true)
	{
		while (a[++i] < y&&i < r);
		while (a[--j] > y);
		if (i >= j) break;
		Swap(a[i], a[j]);
	}
	Swap(a[p], a[j]);
	return j;
}
void QuickSort(int a[], int p, int r)
{
	if (p < r)
	{
		int q = Partition(a, p, r, a[p]);
		QuickSort(a, p, q - 1);
		QuickSort(a, q + 1, r);
	}
}
int Mid(int a[], int p)
{
	int b[5];
	int i;
	for (i = 0; i < 5; ++i)
		b[i] = a[p + i];
	BubbleSort(b, 0, 4);
	for (i = 0; i < 5; ++i)
		if (b[2] == a[p + i])
			return (p + i);
}
//�����ӡ���������ǵ�ʱ������⣬ֻ��ӡ��ǰ��һ�������ݣ���֤�������ȷ�Լ���
void Output(int *R, int start, int terminal) //�����Ĳ���Ϊ����������ʼ��ӡ�㣬��ֹ��
{
	for (int i = start; i <= terminal; i++)
	{	//�趨���ֵĸ�ʽ��������������ۣ�����Ϊ6λ
		cout << setw(6) << R[i];
		if (i % 10 == 0)//ÿһ�����ʮ������
			cout << endl;
	}
}
int Select(int a[], int p, int r, int k)
{
	if (r - p < 5)
	{
		QuickSort(a, p, r);
		return a[p + k - 1];
	}
	int x, i, j;
	for (i = 0; i < (r - p - 4) / 5; i++)
	{
		Swap(a[p + i], a[Mid(a, p + 5 * i)]);
	}
	x = Select(a, p, p + (r - p - 4) / 5, (r - p - 4) / 10 + 1);
	i = Partition(a, p, r, x), j = i - p + 1;
	if (k <= j) return Select(a, p, i, k);
	else return Select(a, i + 1, r, k - j);
}
int  main()
{
	int a[MaxSize];
	int j, k;
	cout << "������Ԫ���ܸ�����" << endl;
	cin >> j;
	srand((unsigned)time(NULL));
	for (int i = 1; i <= j; i++)
	{
		a[i] = rand();
	}
	cout<<"���ɵ����������:"<<endl;
	Output(a,1,200);

	cout << "������Ҫ���Ԫ�صĵڼ�С" << endl;
	cin >> k;
	cout << "��" << k << "СԪ����" << Select(a, 0, j - 1, k);

}
