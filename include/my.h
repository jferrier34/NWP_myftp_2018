/*
** EPITECH PROJECT, 2019
** Project name
** File description:
** Description
*/

#ifndef MY_H_
#define MY_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void my_noop(int client);
int password_check(int sock, FILE *need);
void command_user(int sock);
void my_quit(int client);
char **my_tabb(char *tab);
int user_check(int sock, FILE *need);
void command_all(int client, char *recup);
void login_user(int sock);
void error(int ac, char **av);
struct sockaddr_in complete_addr(char **av);
void main_fonct(int sock, struct sockaddr_in addr);
void complete_info(char **av);


#endif /* !MY_H_ */