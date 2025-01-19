NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -DMACOSX_DEPLOYMENT_TARGET=12.7

export MACOSX_DEPLOYMENT_TARGET = 12.7

LIBMLX	= ./lib/MLX42
LIBFT_DIR	= ./lib/libft
LIBFT	= $(LIBFT_DIR)/libft.a
LDFLAGS = -L/usr/local/opt/glfw/lib

HEADERS	:= -I ./include -I $(LIBMLX)/include -I /opt/homebrew/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT) -L/opt/homebrew/lib

SRCS_DIR = src
OBJ_DIR = obj

SRCS	= $(addprefix $(SRCS_DIR)/, main.c input/check.c input/check_line.c input/check_key_value.c input/check_key_extras.c input/free_error_input.c errors_free_and_exit.c parsing/parsing.c parsing/color_conversion.c \
parsing/map_parsing.c parsing/directions_parsing.c parsing/validate_map.c utils/extra.c rendering/prepare_game.c rendering/extras.c rendering/player_movement.c rendering/hooks.c \
rendering/raycasting.c rendering/3D_rendering.c rendering/draw_minimap.c rendering/draw_miniplayer.c)

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
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) $(HEADERS) -o $(NAME)

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
