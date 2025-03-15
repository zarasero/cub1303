NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
SRC = ft_isalnum.c ft_isalpha.c \
	ft_isdigit.c ft_isascii.c ft_isprint.c \
	ft_bzero.c \
	ft_memset.c \
	ft_memcpy.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_strndup.c \
	ft_memcmp.c \
	ft_memchr.c \
	ft_strnstr.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strncpy.c \
	ft_calloc.c \
	ft_atoi.c \
	ft_memmove.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_strtrim.c \
	ft_split.c \
	ft_atol.c \
	ft_striteri.c \
	ft_strmapi.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	printf/ft_printf.c \
	printf/ft_printf_utils.c \
	printf/ft_fprintf.c \
	printf/ft_fprintf_utils.c \
	ft_lstadd_front.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_substr.c \
	ft_itoa.c \
	ft_strlen.c \
	ft_strjoin.c \
	ft_strdup.c \

RM = rm -f

OBJ = $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) #libftprintf.a
	ar rcs $(NAME) $(OBJ)

#libftprintf.a:
#	$(MAKE) -C printf

bonus: $(OBJ) $(OBJ_B)
	ar rcs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)

re: fclean all bonus

.PHONY: all bonus clean fclean re