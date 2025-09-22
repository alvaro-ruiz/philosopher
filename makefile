# Nombre del ejecutable
NAME = philo

# Archivos fuente
SRCS = src/main.c \
       src/actions.c \
       src/utils.c \
	   src/utils1.c \
       src/monitoring.c

# Objetos
OBJS = ${SRCS:.c=.o}

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3

# Comando para eliminar archivos
RM = rm -f

# Regla por defecto
all: ${NAME}

# Compilación de archivos objeto
%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

# Compilación del ejecutable
${NAME}: ${OBJS}
	@${CC} ${OBJS} ${CFLAGS} -o ${NAME}
	@echo "✅ philo compiled successfully"

# Limpiar archivos objeto
clean:
	@${RM} ${OBJS}
	@echo "🧹 Object files cleaned"

# Limpiar todo
fclean: clean
	@${RM} ${NAME}
	@echo "🧹 Executable cleaned"

# Recompilar
re: fclean all

# Test básicos
test1:
	@echo "🧪 Test 1: 1 800 200 200 (should die)"
	@./$(NAME) 1 800 200 200

test2:
	@echo "🧪 Test 2: 5 800 200 200 (no one should die)"
	@./$(NAME) 5 800 200 200

test3:
	@echo "🧪 Test 3: 5 800 200 200 7 (should stop after 7 meals)"
	@./$(NAME) 5 800 200 200 7

test4:
	@echo "🧪 Test 4: 4 410 200 200 (no one should die)"
	@./$(NAME) 4 410 200 200

test5:
	@echo "🧪 Test 5: 4 310 200 100 (one should die)"
	@./$(NAME) 4 310 200 100

# Verificar memory leaks con valgrind
valgrind:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(NAME) 5 800 200 200 7

# Verificar data races con helgrind
helgrind:
	valgrind --tool=helgrind ./$(NAME) 5 800 200 200 7

# Verificar data races con drd
drd:
	valgrind --tool=drd ./$(NAME) 5 800 200 200 7

.PHONY: all clean fclean re test1 test2 test3 test4 test5 valgrind helgrind drd