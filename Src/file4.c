/*
** EPITECH PROJECT, 2019
** Project name
** File description:
** Description
*/

#include "../include/my.h"

void my_help(int client)
{
    send(client, "214 Help message.\r\n", 19, 0);
}
 
void my_pwd(int client, char *dir)
{
    dprintf(client, "257 \"%s\" created.\r\n", dir);
}