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
	for (t_addr *ptr = globals.addresses; ptr; ptr = ptr->next) {
		ft_printf("%s", ptr->name);
		if (ptr->next)
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

	sleep(ptr->nb + 1);
	ft_printf("Thread %d: nbport=%d start=%d scan:address:port=(", ptr->nb, ptr->ports_nb, ptr->index);
	for (int i = 0; i < ptr->ports_nb; i++) {
		int scan_nb = ((ptr->index + i) / glob->ports_nb) % glob->scans_nb;
		int addr_nb = (ptr->index + i) / (glob->ports_nb * glob->scans_nb);
		int port_nb = (ptr->index + i) % glob->ports_nb;
		t_addr *addr = glob->addresses;
		while (addr_nb-- > 0)
			addr = addr->next;
		ft_printf("%s:%s:%d,", glob->scans[scan_nb], addr->name, glob->ports[port_nb]);
	}
	ft_printf(")\n");
	pthread_exit(NULL);
}

static void 	instantiate_threads()
{
	return;
	t_thread	*ptr		= NULL;
	int 		total		= globals.addresses_nb * globals.ports_nb * globals.scans_nb; // Total number of operation to be performed.
	int 		ports_nb	= total / globals.threads_nb; // Number of operations per thread.
	int 		index 		= 0;
	int 		i 			= 0;

	globals.threads = ft_memalloc(sizeof(*globals.threads) * globals.threads_nb);
	if (globals.threads == NULL)
		nmap_error("%s: threads allocation failed.", globals.progname);
	while (i < globals.threads_nb && i < total) {
		globals.threads[i] = malloc(sizeof(**globals.threads));
		if (globals.threads[i] == NULL)
			nmap_error("%s: Thread No %d: Allocation failed.", globals.progname, i);
		ptr = globals.threads[i];
		ptr->nb = i;
 		/* Number of total operations to perform and threads can be unpaired */
 		int ports_plus 	= (i < total % globals.threads_nb) ? 1 : 0;
		ptr->ports_nb = ports_nb + ports_plus;
		ptr->index = index;
		ptr->global = &globals;
		if (pthread_create(&ptr->id, NULL, routine_threads, ptr))
			nmap_error("%s: Thread No %d: Creation failed.", globals.progname, i);
		ft_printf("Thread %d created.\n", i);
		index += ptr->ports_nb;
		i++;
	}
	i = 0;
	while (i < globals.threads_nb && i < total) {
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
	get_interface();
	get_hosts_addr();
	if (globals.addresses_nb > 0) {
		if (init_pcap(0, 0, 0, "")) {
			ping_scan();
			instantiate_threads();
		}
	}
}
