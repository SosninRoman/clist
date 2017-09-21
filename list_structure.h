#ifndef LST_STRUCT
#define LST_STRUCT
#include <stdlib.h>

typedef struct node
{
	void* data;
	struct node* next;
	struct node* prev;
}node ;

typedef struct list
{
	void* rep;
}list ;

typedef node* link;

list*  ls_create(int type_size);

void   ls_destroy(list** lst);

void   ls_insert(list* lst, const void* data, node* next_node);

node*  ls_erase(list* lst, node* target);

int    ls_size(list* lst);

node*  ls_head(list* lst);

#endif