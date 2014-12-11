#include	"entete1.h"

void
nozo(int signo)
{
	pid_t	pid;
	int	stat;

	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("fils %d terminé\n", pid);
	return;
}
