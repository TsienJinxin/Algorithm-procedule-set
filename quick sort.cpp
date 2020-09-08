#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
#define MAX 99999     //数组最大容量 

void insertsort(int *R,int length)   //插入排序 
{
	int i,j,temp;
	for(i=1;i<length;i++)
	{
		if(R[i]<R[i-1])
		{
			temp=R[i];
			R[i]=R[i-1];
			for(j=i-2;temp<R[j]&&j>=0;j--)
				R[j+1]=R[j];
			R[j+1]=temp;
		}
	}
}
void print(int *r,int s,int t)//打印数组 
{
	for(int i=s;i<=t;i++)
	{
		cout<<r[i]<<" ";
		if(i%20==0)
			cout<<endl;
		}	
	cout<<endl;cout<<endl;
}
int quickpass(int *R,int low ,int high)//快速排序定位 
{
	R[0]=R[low];
	int pivotkey = R[low];
	while(low<high)
	{
		while(low<high && R[high]>=pivotkey) high--;
		R[low]=R[high];
		while(low<high && R[low]<=pivotkey) low++;
		R[high]=R[low];
	}
	R[low] = R[0];
	return low;	
}

void quicksort(int *r,int low,int high)//快速排序 
{
	int pivotloc;
	if(high-low<20)						//当子序列长度小于20时改用插入排序 
		insertsort(r+low,high-low+1);
	else
	{
		pivotloc = quickpass(r,low,high);			
		quicksort(r,low,pivotloc-1);			
		quicksort(r,pivotloc+1,high); 
	}
}
int newquickpass(int *R,int low,int high)//三者去中定位 
{
	
	int pivotkey,temp;	
	if((R[high]-R[low])*(R[high]-R[(low+high)/2])<0)
	{
		temp=R[low];
		R[low]=R[high];
		R[high]=temp;
	}
	if((R[(low+high)/2]-R[high])*(R[(low+high)/2]-R[low])<0)
	{
		temp=R[low];
		R[low]=R[(low+high)/2];
		R[(low+high)/2]=temp;
	}
	R[0]=R[low];	
	pivotkey=R[low];
	
	while(low<high)
	{
		while(low<high && R[high]>=pivotkey) high--;
		R[low]=R[high];
		while(low<high && R[low]<=pivotkey) low++;
		R[high]=R[low];
	}
	R[low]=R[0];
	return low;
}
void newquicksort(int *r,int low,int high)//三者去中快速排序 
{	int pivotloc;
	if(high-low<20)	
		insertsort(r+low,high-low+1);
	else
	{		
		pivotloc = newquickpass(r,low,high);
		newquicksort(r,low,pivotloc-1);
		newquicksort(r,pivotloc+1,high);
	}
}

int main()
{
	int array1[MAX],array2[MAX];
	int n;
	clock_t count1,count2; 
	cout<<"请输入元素个数：";
	cin>>n;
	srand((unsigned) time(NULL));
	for(int i=1;i<=n;i++)
	{
		array1[i]=rand();
		array2[i]=array1[i];	
	}
	print(array1,1,200);

	count1=clock();	
	quicksort(array1,1,n);
	count2=clock();
	cout<<"快速排序时间为"<<count2-count1<<endl; 
	print(array1,1,200);	

	count1=clock();	
	quicksort(array1,1,n);
	count2=clock();
	cout<<"快速排序2时间为"<<count2-count1<<endl; 
	print(array1,1,200);
		
	count1=clock();
	newquicksort(array2,1,n);
	count2=clock();
	cout<<"三者取中法快速排序时间为"<<count2-count1<<endl; 
	print(array2,1,200);
	
	count1=clock();
	newquicksort(array2,1,n);
	count2=clock();
	cout<<"三者取中法快速排序2时间为"<<count2-count1<<endl; 
	print(array2,1,200);
	return 0;
}


