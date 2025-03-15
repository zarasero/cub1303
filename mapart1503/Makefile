NAME = cub3d

# Исходные файлы
SOURCES = raycast/draw.c raycast/move.c raycast/init.c raycast/raycast.c raycast/utils1.c
# Объектные файлы
OBJECTS = $(SOURCES:.c=.o)

cub3d: $(OBJECTS)
	cc -Wall -Werror -Wextra -I./mlx -g3 $(OBJECTS) -L./minilibx-linux -lmlx -lXext -lX11 -lm -o cub3d
# Флаги компилятора
CFLAGS = -Wall -Werror -Wextra -I./mlx -I. -g3



# Линковочные флаги для MinilibX
LIBS = -L./minilibx-linux -lmlx -lXext -lX11 -lm


# Компилятор
CC = cc

# Основная цель
all: $(NAME)

# Правило для создания исполняемого файла
$(NAME): $(OBJECTS)
	@echo "Linking $@"
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)

# Правило для создания объектного файла из исходного
%.o: %.c
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка объектных файлов
clean:
	@echo "Cleaning object files"
	rm -f $(OBJECTS)

# Очистка всех файлов, включая исполняемый
fclean: clean
	@echo "Cleaning executable"
	rm -f $(NAME)

# Полная пересборка
re: fclean all

# Указание, что цели не являются файлами
.PHONY: all clean fclean re

