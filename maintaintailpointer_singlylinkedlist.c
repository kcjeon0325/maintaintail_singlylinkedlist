#include <stdio.h>
#include <stdlib.h>

typedef struct elementS {
	int data;
	struct elementS *next;
} element;

element *head, *tail;

int delete(element *elem);
int insertafter(element *elem, int data);
element *insert_sllist(int data);
int init_sllist(void);

int init_sllist()
{
	head = tail = NULL;
	return 1;
}

element *insert_sllist(int data)
{
	element *new;

	new = malloc(sizeof(element));
	if(!new)
	{
		printf("fail to alloc memory %d %s\n", __LINE__, __FILE__);
		return 0;
	}
	printf("added %p %d %d %s\n", new, data, __LINE__, __FILE__);
	new->data = data;
	if(!head)
	{
		head = new;
		return new;
	}
	new->next = head;
	head = new;
	return new;
}

int delete(element *elem)
{
	element *curpos;

	if(elem == head)
	{
		head = head->next;
		free(elem);
		if(!head)
		{
			tail = NULL;
			printf("tail NULL %d %s\n", __LINE__, __FILE__);
		}
		printf("free %p %d %s\n", elem, __LINE__, __FILE__);
		return 1;
	}

	curpos = head;

	while(curpos)
	{
		if(curpos->next == elem)
		{
			curpos->next = elem->next;
			free(elem);
			if(!curpos->next)
			{
				tail = curpos;
				printf("tail %p %d %s\n", tail, __LINE__, __FILE__);
			}
			printf("free %p %d %s\n", elem, __LINE__, __FILE__);
			return 1;
		}
		curpos = curpos->next;
	}
	printf("no data found %p %d %s\n", elem, __LINE__, __FILE__);
	return 0;
}

int insertafter(element *elem, int data)
{
	element *curpos, *new;

	new = malloc(sizeof(element));
	if(!new)
	{
		printf("fail to alloc memory %d %s\n", __LINE__, __FILE__);
		return 0;
	}
	new->data  = data;

	if(!elem)
	{
		new->next = head;
		head = new;

		if(!tail) tail = new;
		return 1;
	}
	curpos = head;
	while(curpos)
	{
		if(curpos->next == elem)
		{
			new->next = curpos->next;
			curpos->next = new;
			printf("added %p %d %s\n", new, __LINE__, __FILE__);
			if(!(new->next))
			{
				tail = new;
			}
			return 1;
		}
		curpos = curpos->next;
	}
	free(new);
	printf("no data found %p %d %s\n", elem, __LINE__, __FILE__);
	return 0;
}

int display_sllist()
{
	element *current = head;

	while(current)
	{
		printf("%p %d\n", current, current->data);
		current = current->next;
	}
}
int main()
{
	element *temp;

	init_sllist();
	insert_sllist(1);
	temp = insert_sllist(2);
	delete(temp);
	temp = insert_sllist(3);
	insert_sllist(4);
	insertafter(temp, 5);
	display_sllist();
}