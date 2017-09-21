#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int				main()
{
	char		ppid[16];
	pid_t		pid;
	int			status;
	char		*arg[3];
	extern char	**environ;

	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else if (pid == 0)
	{
		snprintf(ppid, sizeof(ppid), "%i", getpid());
		arg[0] = "/challenge/cryptanalyse/ch21/ch21";
		arg[1] = crypt(ppid, "$1$awesome");
		arg[2] = NULL;
		printf("%s", arg[1]);
		execve(*arg, arg, environ);
		printf("\nERROR\n");
		exit(0);
	}
	return 0;
}
