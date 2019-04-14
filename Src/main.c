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


void command_user(int sock, char **av)
{
    login_user(sock, av);
}


int main(int ac, char **av)
{
    error(ac, av);
    complete_info(av);
    return (0);
}