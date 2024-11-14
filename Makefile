NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

LIBMLX	= ./lib/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include -I
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS_DIR = src
OBJ_DIR = obj

SRCS	:= $(addprefix $(SRCS_DIR)/, main.c input_check.c parsing.c)
OBJS	:= $(patsubst $(SRCS_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(LIBMLX)/build/libmlx42.a:
	@cmake -S $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4

$(NAME): lib/MLX42/build/libmlx42.a $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re libmlx