#include "all.h"
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>

static void 	print_start()
{
	char 	*scan[] = { "SYN",  "NULL",  "FIN",  "XMAS",  "ACK",  "UDP",  NULL };
	int 	type[] = { NM_SYN, NM_NULL, NM_FIN, NM_XMAS, NM_ACK, NM_UDP };

	ft_printf("Scan Configuration\n");
	ft_printf("Target IP-Address     : ");
	for (int i = 0; globals.addresses[i]; i++) {
		ft_printf("%s", globals.addresses[i]);
		if (globals.addresses[i + 1])
			ft_printf(", ");
	}
	ft_printf(" (%d)\n", globals.addresses_nb);
	ft_printf("No of Ports to scan   : %d\n", globals.ports_nb);
	ft_printf("Scans to be performed : ");
	for (int i = 0; scan[i]; i++) {
		if (globals.scans_types & type[i])
			ft_printf("%s ", scan[i]);
	}
	ft_printf(" (%d)\n", globals.scans_nb);
	ft_printf("No of threads         : %d\n", globals.threads_nb);
}

static void 	*routine_threads(void *data)
{
	if (data == NULL)
		nmap_error("%s: Data from thread routine is NULL.", globals.progname);

	t_thread	*ptr 		= (t_thread *)data;
	t_global 	*glob 		= ptr->global;
	int 		total 		= glob->addresses_nb * glob->ports_nb * glob->scans_nb;
	int 		ports_nb 	= (total / glob->threads_nb > 0) ? total / glob->threads_nb : 1;
	int 		start 		= ptr->nb * ports_nb % glob->ports_nb;
	int 		scan_type 	= 0;

	sleep(1);
	int 	type[]  = { NM_SYN, NM_NULL, NM_FIN, NM_XMAS, NM_ACK, NM_UDP };
	for (int i = 0, nb = ptr->nb * ports_nb / glob->ports_nb; i < 6; i++) {
		if (glob->scans_types & type[i]) {
			if (nb == 0) {
				scan_type = type[i];
				break ;
			}
			nb--;
		}
	}
	ft_printf("Thread %d: SCAN=%x nbport=%d start=%d ports=", ptr->nb, scan_type, ports_nb, start);
	for (int i = 0; i < ports_nb; i++) {
		ft_printf("%d,", glob->ports[(start + i) % glob->ports_nb]);
	}
	ft_printf("\n");
	pthread_exit(NULL);
}

static void 	instantiate_threads()
{
	t_thread	*ptr 				= NULL;
	int 		total_calls			= globals.addresses_nb * globals.ports_nb * globals.scans_nb;
	int 		i;

	globals.threads = ft_memalloc(sizeof(*globals.threads) * globals.threads_nb);
	if (globals.threads == NULL)
		nmap_error("%s: threads allocation failed.", globals.progname);
	i = 0;
	while (i < globals.threads_nb && i < total_calls) {
		globals.threads[i] = malloc(sizeof(**globals.threads));
		if (globals.threads[i] == NULL)
			nmap_error("%s: Thread No %d: Allocation failed.", globals.progname, i);
		ptr = globals.threads[i];
		ptr->nb = i;
		ptr->global = &globals;
		if (pthread_create(&ptr->id, NULL, routine_threads, ptr))
			nmap_error("%s: Thread No %d: Creation failed.", globals.progname, i);
		ft_printf("Thread %d created.\n", i);
		i++;
	}
	i = 0;
	while (i < globals.threads_nb && i < total_calls) {
		ptr = globals.threads[i];
		if (ptr->id)
			pthread_join(ptr->id, NULL);
		i++;
	}
	ft_printf("All threads terminated.\n");
}

void 			start_mapping()
{
	print_start();
	instantiate_threads();
}