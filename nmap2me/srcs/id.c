
#include "all.h"

int			get_id(void)
{
	static int	id = 59000;
	int			ret;

	pthread_mutex_lock(&g_global.id_lock);
	ret = id++;
	pthread_mutex_unlock(&g_global.id_lock);
	return (ret);
}
