# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damachad <damachad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 10:57:36 by damachad          #+#    #+#              #
#    Updated: 2023/08/02 12:30:16 by damachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ COLORS /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ COMMANDS /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
CC = cc
RM = rm -rf

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ FLAGS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
CFLAGS 	= -Wall -Werror -Wextra
MK_FLAG = --no-print-directory
LFLAGS 	= -L ./libft -lft -L ./mlx -lmlx -lXext -lX11 -lm -lbsd

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ PATHS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
INC			= includes
MAP_DIR		= maps
SRC_DIR		= srcs
OBJ_DIR		= objs
SRC_BNS_DIR	= srcs_bonus
OBJ_BNS_DIR	= objs_bonus

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ FILES _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
NAME 		= so_long
NAME_BNS	= so_long_bonus
LIBFT		= libft/libft.a
MLX			= mlx/libmlx.a
MAP			= valid2.ber
FILES 		= checker clean main map move render init
FILES_BNS 	= checker_bonus clean_bonus main_bonus map_bonus move_bonus \
			render_bonus init_bonus
SRC 		= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))
SRC_BNS		= $(addprefix $(SRC_BNS_DIR)/, $(addsuffix .c, $(FILES_BNS)))
OBJ_BNS		= $(addprefix $(OBJ_BNS_DIR)/, $(addsuffix .o, $(FILES_BNS)))

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ RULES _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME) -I $(INC)
	@echo "[$(GREEN)$(NAME) created$(RESET)]"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c 
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "[$(GREEN)so_long objs directory created$(RESET)]"

$(MLX):
	@make $(MK_FLAG) -sC mlx
	@echo "[$(GREEN)libmlx.a created$(RESET)]"

$(LIBFT):
	@make $(MK_FLAG) -C ./libft

clean:
	@$(RM) $(OBJ_DIR) $(OBJ_BNS_DIR)
	@make $(MK_FLAG) -C ./libft clean
	@make $(MK_FLAG) -C ./mlx clean
	@echo "[$(RED)objs removed$(RESET)]"

fclean: clean
	@$(RM) $(NAME) $(NAME_BNS) $(LIBFT)
	@echo "[$(RED)executables and $(LIBFT) removed$(RESET)]"

re: fclean all

bonus: $(NAME_BNS)

$(NAME_BNS): $(OBJ_BNS_DIR) $(OBJ_BNS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ_BNS) $(LFLAGS) -o $(NAME_BNS) -I $(INC)
	@echo "[$(GREEN)$(NAME) created$(RESET)]"

$(OBJ_BNS_DIR):
	@mkdir -p $(OBJ_BNS_DIR)
	@echo "[$(GREEN)so_long_bonus objs directory created$(RESET)]"

$(OBJ_BNS_DIR)/%.o : $(SRC_BNS_DIR)/%.c 
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

# valgrind --leak-check=full -s --show-leak-kinds=all --track-origins=yes

reb: fclean bonus

test: re
	@./$(NAME) "$(MAP_DIR)/$(MAP)"

test_bns: reb
	@./$(NAME_BNS) "$(MAP_DIR)/$(MAP)"

.PHONY: all clean fclean re test bonus reb test_bns
