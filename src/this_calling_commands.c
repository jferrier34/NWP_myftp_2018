/*
** EPITECH PROJECT, 2019
** Project name
** File description:
** Description
*/

#include "../include/my.h"

void quit(int client)
{
    if (send(client, "221 Service closing control connection.\r\n", 41, 0)
    == -1)
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
        if (send(sock, "331 User name okay, need password.\r\n", 36, 0) < 0)
            exit(84);
        return (1);
    }
    return (0);
}

void command_all(int client, char *recup, char **av)
{
    char **my_tab;
    my_tab = my_tabb(recup);
    if (strcmp(my_tab[0], "QUIT") == 0)
        quit(client);
    if (strcmp(my_tab[0], "NOOP") == 0)
        noop(client);
    if (strcmp(my_tab[0], "HELP") == 0)
        help(client);
    if (strcmp(my_tab[0], "PWD") == 0)
        pwd(client, av[2]);
}

void login_user(int sock, char **av)
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
            command_all(sock, recup, av);
        shutdown(sock, 2);
        fclose(need);
        exit(0);
    }
    return;
}