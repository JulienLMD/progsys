#include	"entete1.h"

void
str_echo(int sockfd)
{
	ssize_t		n;
	char		line[MAXLINE];

	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connexion fermée par l'autre bout */

		Writen(sockfd, line, n);
	}
}
