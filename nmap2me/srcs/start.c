#include "all.h"
#include "ft_printf.h"

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
		if (globals.scan_types & type[i])
			ft_printf("%s ", scan[i]);
	}
	ft_printf(" (%d)\n", globals.scan_nb);
	ft_printf("No of threads         : %d\n", globals.threads_nb);
}

void 			start_mapping()
{
	print_start();
}