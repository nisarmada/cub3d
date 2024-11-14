NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES = ft_strlen.c ft_putnbr_fd.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
    ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
    ft_memcpy.c ft_memmove.c ft_memset.c ft_split.c ft_strchr.c ft_strdup.c \
    ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
    ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_striteri.c ft_putchar_fd.c \
    ft_putendl_fd.c ft_putstr_fd.c ft_strmapi.c ft_itoa.c get_next_line.c ft_chars.c \
	ft_numbers.c ft_printf.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_strcpy.c

# BONUS_SOURCES = ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
#     ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstnew.c

OBJECTS = $(SOURCES:.c=.o)

# BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)
AR = ar -rcs

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)

$(OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

bonus: $(BONUS_OBJECTS)
	$(AR) $(NAME) $(BONUS_OBJECTS)

$(BONUS_OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus