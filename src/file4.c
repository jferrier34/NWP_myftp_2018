/*
** EPITECH PROJECT, 2019
** Project name
** File description:
** Description
*/

#include "../include/my.h"

void help(int client)
{
    send(client, "214 Help message.\r\n", 19, 0);
}
 
void pwd(int client, char *dir)
{
    dprintf(client, "257 \"%s\" created.\r\n", dir);
}