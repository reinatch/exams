#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
//- add select globals/state for multi-client server 
int g_sock, g_max, g_id;
int g_ids[65536];
char *g_bufs[65536];
fd_set g_all, g_rd, g_wr;
//fatal error
void fatal(void){
	write(2, "Fatal error\n", 12);
	exit(1);
}
//ADD strjoin ans extract_msg
void notify_all(int skip_fd, char *msg){
	int	fd;
	fd = 0;
	while (fd <= g_max){
		if (FD_ISSET(fd, &g_wr) && fd != skip_fd && fd != g_sock)
			send(fd, msg, strlen(msg), 0);
		fd++;
	}
}
//accept repeatedly in event loop
void add_client(void){
	int		fd;
	char	msg[64];
	fd = accept(g_sock, 0, 0);
	if (fd < 0)
		return ;
	if (fd > g_max)
		g_max = fd;
	g_ids[fd] = g_id++;
	g_bufs[fd] = 0;
	FD_SET(fd, &g_all);
	sprintf(msg, "server: client %d just arrived\n", g_ids[fd]);
	notify_all(fd, msg);
}
//proper client cleanup + leave broadcast
void del_client(int fd){
	char	msg[64];
	sprintf(msg, "server: client %d just left\n", g_ids[fd]);
	notify_all(fd, msg);
	FD_CLR(fd, &g_all);
	free(g_bufs[fd]);
	g_bufs[fd] = 0;
	close(fd);
}
//recv, accumulate, split by '\n', rebroadcast
void read_client(int fd){
	char	rbuf[1001];
	char	*line;
	char	*full;
	int		n;
	int		st;
	n = recv(fd, rbuf, 1000, 0);
	if (n <= 0)
		return ((void)del_client(fd));
	rbuf[n] = 0;
	g_bufs[fd] = str_join(g_bufs[fd], rbuf);
	if (!g_bufs[fd])
		fatal();
	while (1){
		st = extract_message(&g_bufs[fd], &line);
		if (st < 0)
			fatal();
		if (st == 0)
			break ;
		full = malloc(strlen(line) + 32);
		if (!full)
			fatal();
		sprintf(full, "client %d: %s", g_ids[fd], line);
		notify_all(fd, full);
		free(full);
		free(line);
	}
}
int main(int ac, char **av){
	struct sockaddr_in	sa;
	//check port
	if (ac != 2)
		return (write(2, "Wrong number of arguments\n", 26), 1);
	//CHANGE: remove printf/exit blocks, use fatal()
	g_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (g_sock < 0)
		fatal();
	// initialize fd_set/select state 
	g_max = g_sock;
	FD_ZERO(&g_all);
	FD_SET(g_sock, &g_all);
	//used fixed 8081; exam uses argv[1]
	bzero(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(2130706433);
	sa.sin_port = htons(atoi(av[1]));
	if (bind(g_sock, (const struct sockaddr *)&sa, sizeof(sa)) != 0)
		fatal();
	if (listen(g_sock, 128) != 0)
		fatal();
	//replace one-time accept() with infinite select() server loop
	while (1){
		int	fd;
		g_rd = g_wr = g_all;
		if (select(g_max + 1, &g_rd, &g_wr, 0, 0) < 0)
			continue ;
		fd = 0;
		while (fd <= g_max){
			if (FD_ISSET(fd, &g_rd)){
				if (fd == g_sock)
					add_client();
				else
					read_client(fd);
			}
			fd++;
		}
	}
}
