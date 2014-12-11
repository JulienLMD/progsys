
/* Boucle de traitement du client : lecture d'une ligne de texte à partir de 
 * l'entrée standard, son écriture sur le serveur, lecture de l'écho du serveur
 * et écriture de cette ligne d'écho sur la sortie standard.
*/
#include	"entete1.h"

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: terminaison prématurée du serveur");

		Fputs(recvline, stdout);
	}
}
