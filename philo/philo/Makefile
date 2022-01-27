NAME := philo

SRCS =  ./source/philo.c \
		./source/myusleep.c \
		./source/atois.c \
		./source/utils.c \

OBJS = ${SRCS:.c=.o}

LIBFT_DIR := ./libft/
INC_DIR := .
EXE_DIR = ./

CC := cc 
GCC := gcc 
CFLAGS := -Wall -Wextra -Werror
MV := mv -f
RM := rm -f

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -I $(INC_DIR) -o $@ 

$(NAME):  $(OBJS)
	gcc ./source/*.o -o philo



all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re

