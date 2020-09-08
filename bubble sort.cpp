#include<iostream>
#include<string.h>
#include<string>
#include<stdio.h>

using namespace std;
void Sort(int a[],int n)
{
	int temp;
	for(int i=0;i<n;i++)
		for (int j = i; j < n; j++)
		{
			if (a[j] < a[j-1])
			{
				temp = a[j];
				a[j] = a[j-1];
				a[j-1] = temp;
			}
				
		}
}

void Display(int a[],int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i]<<"\t";
	}
}
int main()
{
	int a[10] = { 1,2,3,45,6,89,4,61,5,7 };
	Sort(a, 10);
	Display(a, 10);
	cin.get();
	return 0;

}