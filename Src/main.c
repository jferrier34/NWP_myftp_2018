/*
** EPITECH PROJECT, 2019
** Project name
** File description:
** Description
*/

#include "../include/my.h"

void my_noop(int client)
{
    if (send(client, "200 Command okay.\r\n", 19, 0) == -1)
        exit (84);
}

void my_quit(int client)
{
    if (send(client, "221 Service closing control connection.\r\n", 41, 0) == -1)
        exit (0);
    shutdown(client, 2);
    exit(0);
}

char **my_tabb(char *tab)
{
    char **my_tab = malloc(sizeof(char *) * 3);
    my_tab[0] = strtok(tab, "\r ");
    my_tab[1] = strtok(NULL, "\r ");
    my_tab[2] = NULL;
    return (my_tab);
}

int user_check(int sock, FILE *need)
{
    char tab[] = "Anonymous";
    char **dubl_tab;
    size_t size = 0;
    char *dir = NULL;
    if (getline(&dir, &size, need) == -1)
        exit (84);
    dubl_tab = my_tabb(dir);
    if (strcmp(dubl_tab[0], "USER") != 0) {
        send(sock, "332 Need account for login.\r\n", 29, 0);
        return (0);
    }
    if (strcmp(dubl_tab[1], tab) == 0) {
        if(send(sock, "331 User name okay, need password.\r\n", 36, 0) < 0)
            exit(84);
        return (1);
    }
    return (0);
}

int password_check(int sock, FILE *need)
{
    char tab[] = "\n";
    char **dubl_tab;
    size_t size = 0;
    char *dir = NULL;
    if (getline(&dir, &size, need) == -1)
        exit (84);
    dubl_tab = my_tabb(dir);
    if (strcmp(dubl_tab[0], "PASS") != 0) { 
        send(sock, "332 Need account for login.\r\n", 29, 0);
        return (0);
    }
    if (strcmp(dubl_tab[1], tab) == 0) {
        if(send(sock, "230 User logged in, proceed.\r\n", 30, 0) < 0)
            exit (84);
        return (1);
    }
    return (0);
}

void command_all(int client, char *recup)
{
    char **my_tab;
    my_tab = my_tabb(recup);
    if (strcmp(my_tab[0], "QUIT") == 0)
        my_quit(client);
    if (strcmp(my_tab[0], "NOOP") == 0)
        my_noop(client);
}

void login_user(int sock)
{
    int check_user = 0;
    int check_pass = 0;
    size_t size = 0;
    char *recup = NULL;
    FILE *need = fdopen(sock, "r");
    check_user = user_check(sock, need);
    if (check_user == 1)
        check_pass = password_check(sock, need);
    if (check_user == 1 && check_pass == 1) {
        while (getline(&recup, &size, need) != -1)
            command_all(sock, recup);
        shutdown(sock, 2);
        fclose(need);
        exit(0);
    }
    return;
}

void command_user(int sock)
{
    login_user(sock);
}

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

int main(int ac, char **av)
{
    error(ac, av);
    complete_info(av);
    return (0);
}