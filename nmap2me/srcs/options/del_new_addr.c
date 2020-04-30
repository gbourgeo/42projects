
#include "all.h"

void			del_new_addr(t_addr **addr)
{
	t_addr		*ptr;

	if (!addr || !*addr)
		return ;
	ptr = *addr;
	*addr = ptr->next;
	if (ptr->prev)
		ptr->prev->next = ptr->next;
	if (ptr->next)
		ptr->next->prev = ptr->prev;
	ptr->next = NULL;
	free_addresses(&ptr);
}
