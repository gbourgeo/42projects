#include "all.h"

t_data		*find_data(int protocol, int id, t_params *e)
{
	unsigned int	i;

	i = 0;
	(void)protocol;
	while (i < e->total_operations)
	{
		if (e->data[i].id == id)
		{
			return (e->data + i);
		}
		i++;
	}
	return (NULL);
}