NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

LIBMLX	= ./lib/MLX42
LIBFT_DIR	= ./lib/libft
LIBFT	= $(LIBFT_DIR)/libft.a

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)

SRCS_DIR = src
OBJ_DIR = obj

SRCS	= $(addprefix $(SRCS_DIR)/, main.c input_check.c parsing/parsing.c parsing/color_conversion.c \
parsing/map_parsing.c utils/extra.c rendering/prepare_game.c)

OBJS	= $(patsubst $(SRCS_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJ_SUBDIRS = $(sort $(dir $(OBJS)))

GREEN = \033[32m
BLUE = \033[34m
RESET = \033[0m

all: $(LIBFT) $(NAME)

$(LIBMLX)/build/libmlx42.a:
	@cmake -S $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4

$(LIBFT):
	@echo "$(BLUE)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR) > /dev/null
	@echo "$(GREEN)libft built!$(RESET)"

$(NAME): lib/MLX42/build/libmlx42.a $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean > /dev/null
	@rm -rf $(LIBMLX)/build

fclean: clean
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re libmlx
