#include <iostream>

#include <cstdlib>

#include <cstdio>

#include <ctime>

using namespace std;



typedef char ElemType;



typedef struct Node{

	ElemType data;

	struct Node *next;

}Node, *LinkList;



LinkList CreateList()

{

	LinkList L;

	ElemType c;

	L = (LinkList)malloc(sizeof(Node));

	L->next = NULL;

	Node *p , *tail;

	tail = L;

	c = getchar();

	while(c != '#')

	{

		p = (Node *)malloc(sizeof(Node));

		p->data = c;

		tail->next = p;

		tail = p;

		c = getchar();

	}

	tail->next = NULL;

	return L;

}



void ShowList(LinkList L)

{

	Node *p;

	p = L->next;

	while(p != NULL)

	{

		cout << p->data << " ";

		p = p->next;

	}

	cout << endl;

}



void ReverseList(LinkList L)

{

	Node *p, *q;

	p = L->next;

	L->next = NULL;

	while(p != NULL)

	{

		q = p->next;

		p->next = L->next;

		L->next = p;

		p = q;

	}



}



LinkList MergeList1(LinkList LA, LinkList LB)

{

	LinkList LC;

	Node *pa, *pb, *r;

	pa = LA->next;

	pb = LB->next;

	LC = LA;

	LC->next = NULL;

	r = LC;

	while(pa != NULL && pb != NULL)

	{

		if(pa->data <= pb->data)

		{

			r->next = pa;

			r = pa;

			pa = pa->next;

		}

		else

		{

			r->next = pb;

			r = pb;

			pb = pb->next;

		}

		if(pa)

		{

			r->next = pa;

		}

		else

		{

			r->next = pb;

		}

	}

	return LC;

}



LinkList MergeList2(LinkList LA, LinkList LB)

{

	ReverseList(LA);

	ReverseList(LB);

	LinkList LC;

	Node *pa, *pb, *r;

	pa = LA->next;

	pb = LB->next;

	LC = LA;

	LC->next = NULL;

	r = LC;

	while(pa != NULL && pb != NULL)

	{

		if(pa->data <= pb->data)

		{

			r->next = pb;

			r = pb;

			pb = pb->next;

		}

		else

		{

			r->next = pa;

			r = pa;

			pa = pa->next;

		}

		if(pa)

		{

			r->next = pa;

		}

		else

		{

			r->next = pb;

		}

	}

	return LC;

}



int main()

{

	LinkList LA;

	LA = CreateList();

	getchar();

	LinkList LB;

	LB = CreateList();



	cout << "LA:" << endl;

	ShowList(LA);



	cout << "LB:" << endl;

	ShowList(LB);



	LinkList LC;

	LC = MergeList2(LA, LB);

	cout << "MergeList2:" << endl;

	ShowList(LC);



	return 0;

}
