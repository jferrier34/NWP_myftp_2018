/*
** EPITECH PROJECT, 2019
** Project name
** File description:
** Description
*/

#include "../include/my.h"


void error(int ac, char **av)
{
    if (ac != 3)
        exit(84);
    if (chdir(av[2]) == -1)
        exit(84);
}

struct sockaddr_in complete_addr(char **av)
{
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(av[1]));
    return (addr);
}

void main_fonct(int sock, struct sockaddr_in addr)
{
    socklen_t tmp;
    pid_t pid;
    int client_sock = 0;
    while(1) {
        tmp = sizeof(addr);
        if ((client_sock = accept(sock, (struct sockaddr *)&addr, &tmp)) == -1)
            exit(84);
        if (send(client_sock, "220 Service ready for new user.\r\n", 33, 0) == -1) {
            shutdown(client_sock, 2);
            exit(84);
        }
        pid = fork();
        if (pid == 0) {
            command_user(client_sock);
            shutdown(client_sock, 2);
            exit(0);
        }
    }
}

void complete_info(char **av)
{
    struct protoent *proto;
    struct sockaddr_in addr;
    int sock = 0;
    if ((proto = getprotobyname("TCP")) == NULL)
        exit(84);
    if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
        exit(84);
    addr = complete_addr(av);
    if (bind(sock, (const struct sockaddr *)&addr, sizeof(addr)) == -1)
        exit(84);
    if (listen(sock, 42) == -1)
        exit(84);
    main_fonct(sock, addr);
}