#include "list_structure.h"
#include <string.h>

typedef struct list_rep
{
	node* head;
	int   size;
	int   keep_type_size;
} list_rep;

list* ls_create(int type_size)
{
	list* result = (list*) malloc( sizeof(list) );
	result->rep = malloc( sizeof(struct list_rep) );
	
	((struct list_rep*) (result->rep))->head = 0;
	((struct list_rep*) (result->rep))->size = 0;
	((struct list_rep*) (result->rep))->keep_type_size = type_size;

	return result;
};

int ls_size(list* lst)
{
	return ((struct list_rep*)(lst->rep))->size;
}

node* ls_head(list* lst)
{
	return ( (list_rep*)(lst->rep) )->head;
}

void ls_insert(struct list* lst, const void* data, node* next_node)
{
	int type_size = ( (list_rep*) (lst->rep) )->keep_type_size;
	int* sz = &( ( (list_rep*) (lst->rep) )->size);
	node* head;

	if( ! *sz)
	{
		head = ( ( (list_rep*) (lst->rep) )->head = (node*) malloc( sizeof(node) ) );
		head->data = malloc(type_size);
		memcpy(head->data, data, type_size);
		head->next = 0;
		head->prev = 0;				
	}
	else
	{
		link itr = ls_head(lst);
		link new_node = (node*) malloc(sizeof(node));
		new_node->data = malloc(type_size);
		memcpy(new_node->data, data, type_size);
		new_node->next = next_node;

		if(next_node != 0)
		{
			new_node->prev = next_node->prev;
		}
		else
		{
			while(itr->next != 0)
				itr = itr->next;
			new_node->prev = itr;
		}
		if(new_node->prev != 0)
			new_node->prev->next = new_node;
		if(new_node->next != 0)
			new_node->next->prev = new_node;
	}
	(*sz)++;
}

node* ls_erase(list* lst, node* target)
{
	node* result = 0;

	if(target == 0)
		return 0;
	else
		result = target->next;
	
	if(target == ls_head(lst) )
		((list_rep*) (lst->rep) )->head = ((list_rep*) (lst->rep) )->head->next;

	if(target->prev)
		target->prev->next = target->next;
	if(target->next)
		target->next->prev = target->prev;

	free(target->data);
	free(target);

	( (list_rep*) (lst->rep) )->size--;

	return result;
}

void  ls_destroy(list** lst)
{
	link itr = ls_head(*lst);
	link del;

	while(itr != 0)
	{
		del = itr;
		itr = itr->next;
		
		free(del->data);
		free(del);
	}

	free((*lst)->rep);
	free(*lst);
	*lst = 0;
}