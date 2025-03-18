NAME = cub3d

# Исходные файлы
SOURCES =	srcs/parsing.c \
		srcs/utils.c \
		srcs/free.c \
		srcs/textures_and_colors.c \
		srcs/parsing_map.c \
		srcs/clean_file.c \
		srcs/main.c \
		srcs/utils_2.c \
		raycast/draw.c \
		raycast/move.c \
		raycast/init.c \
		raycast/raycast.c \
		raycast/utils1.c

# Объектные файлы
OBJ = $(SOURCES:.c=.o)

# Компилятор
CC = cc

RM = rm -f

# Флаги компилятора
CFLAGS = -Wall -Werror -Wextra -I./mlx -I./libft -g3
#CFLAGS = -Wall -Wextra -g -fsanitize=address -I./mlx -I./libft -g3


# Линковочные флаги для MinilibX
LIBS = -L./minilibx-linux -lmlx -lXext -lX11 -lm -L./libft -lft

# Основная цель
all: $(NAME)

# Правило для создания исполняемого файла
$(NAME): $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

# Правило для создания объектного файла из исходного
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка объектных файлов
libft/libft.a :
	$(MAKE) -C libft

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C libft

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft
	
re: fclean all

# Указание, что цели не являются файлами
.PHONY: all clean fclean re
