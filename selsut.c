 #include "entete2.h"
 fd_set fdvar; 
 FD_ZERO(&fdvar); 
 FD_SET(tcp_sfd,&fdvar); 
 FD_SET(udp_sfd,&fdvar); 
 int maxpl = max(tcp_sfd,udp_sfd); 
 cout << "Waiting for a client...\n";

 if(select(maxpl+1 ,&fdvar,NULL,NULL,NULL)==-1) 
 { 
      perror("error in select"); 
 } 
 if(FD_ISSET(udp_sfd,&fdvar)) 
 { 
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

	dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));
  } 
  else 
  { 
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);


	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

		if ( (childpid = Fork()) == 0) { /* Ici le fils ! */
			Close(listenfd);       /* Fermer la socket à l'écoute */
			str_echo(connfd);	/* traiter la requête */
			exit(0);
		}
		Close(connfd);		/* Le père ferme la socket connectée */
	}
  }
