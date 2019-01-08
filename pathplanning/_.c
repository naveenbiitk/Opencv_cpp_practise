#include <stdio.h>
#include <stdlib.h>


struct stack
{
	int data;
	struct stack *next;
	
};


void initStack(struct stack **s)
{
	*s=NULL;
}


int top(struct stack *s)
{
	return(s->data);
}


void push(struct stack **s, int x)
{
	struct stack *p= (struct stack *)malloc(sizeof(*p));

	if(p==NULL)
	{
		printf(stderr,"Memory allocation failed.\n");
		return;
	}

	p->data=x;
	p->next=*s;
	*s=p;
}


void printStack(struct stack *s)
{
	while(s)
	{
		printf("%d ",s->data);
		s=s->next;
	}
	printf("\n");
}


int pop(struct stack **s)
{
	int x;
	struct stack *temp;

	x=(*s)->data;
	temp=*s;
	(*s)=(*s)->next;
	free(temp);

	return x;
}


void sortedInsert(struct stack **s,int x)
{
	if(isEmpty(*s) || x>top(*s))
	{
		push(s,x);
		return;
	}

	int temp=pop(s);
	sortedInsert(s,x);

	push(s,temp);
}


void sortStack(struct stack **s)
{
	if(!isEmpty(*s))
	{
		int x=pop(s);
		sortStack(s);
		sortedInsert(s,x);
	}
}


int main(void)
{
	struct stack *top;

	initStack(&top);
	push(&top, 30);
	push(&top, -5);
	push(&top, 18);
	push(&top, 14);
	push(&top, -3);

	printf("Stack elements before sorting: \n");
	printStack(top);

	sortStack(&top);
	printf("\n\n");

	printf(" Stack elements after sorting: \n");
	printStack(top);

	return 0;
	
}