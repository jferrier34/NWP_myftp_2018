##
## EPITECH PROJECT, 2019
## PSU_2018_malloc
## File description:
## Makefile
##

all	:	$(NAME)

.PHONY : all

NAME	=	myftp


CFLAGS	=	-Wall -Wextra -pedantic

SRC	=	./Src/main.c	

OBJ	=	$(SRC:.c=.o)


$(NAME)	:	$(OBJ)
		gcc -o $(NAME) $(CFLAGS) $(OBJ)

all	:	$(NAME)

clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	: fclean all