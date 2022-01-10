NAME := philo
LIBFT_NAME = libft.a

SRCS =  ./sources/philo.c \

OBJS = ${SRCS:.c=.o}

LIBFT_DIR := ./libft/
INC_DIR := ./header/
EXE_DIR = ./

CC := cc
GCC := gcc
CFLAGS := -Wall -Wextra -Werror  
MV := mv -f
RM := rm -f

%.o: %.c
	$(CC)  $(CFLAGS) -c $< -I $(INC_DIR) -o $@ 

$(NAME): $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS)
	$(CC) -o $(NAME)  $^ -I $(INC_DIR)

$(LIBFT_DIR)$(LIBFT_NAME): $(LIBFT_DIR)
	make -C $(LIBFT_DIR)

all: $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re

