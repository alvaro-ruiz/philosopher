# Nombre del ejecutable
NAME = philo

SRCS		= src/main.c src/actions.c

OBJS		= ${SRCS:.c=.o}

CC			= cc

CFLAGS = -Wall -Wextra -Werror

RM			= rm -f

all: ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	@${CC} ${OBJS} ${LIBS} -o ${NAME}
	@echo "philo compiled"

clean:
	@${RM} ${OBJS}

fclean:	clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re