#include "list_structure.h"

int main()
{
	list* l = ls_create( sizeof(int) );
	int a = 5;
	int b = 6;
	int d;

	node* itr = ls_head(l);
	ls_insert(l, &a, itr);
	ls_insert(l, &b, itr);
	
	itr = ls_head(l);

	while(itr != 0)
	{
		d = *(int*)(itr->data);				
		if(d == 6)
			itr = ls_erase(l, itr->prev);
		else
			itr = itr->next;
	}

	itr = ls_head(l);
	while(itr != 0)
	{
		d = *(int*)(itr->data);		
		itr = itr->next;
	}

	ls_destroy(&l);

	return 0;
}