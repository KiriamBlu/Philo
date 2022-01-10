NAME	= libft.a

SRCS	=	ft_bzero.c \
			ft_atoispecial.c \
			ft_memset.c \
			ft_memcpy.c \
			ft_calloc.c \
			ft_strchr.c \
			ft_strlen.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_split.c \

OBJS	= $(SRCS:.c=.o)


CFLAGS	= -Wall -Werror -Wextra

CC 		= gcc

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -c ${SRCS}
	ar rcs ${NAME} ${OBJS}

bonus: ${OBJS_B}
	${CC} ${CFLAGS} -c ${SRCS_B}
	ar rcs ${NAME} ${OBJS_B}

clean:
	rm -f ${OBJS} ${OBJS_B}

fclean: clean
	rm -f $(NAME)

re: fclean all bonus

.PHONY: all bonus clean fclean re