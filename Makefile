# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damachad <damachad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 10:57:36 by damachad          #+#    #+#              #
#    Updated: 2023/08/01 11:48:18 by damachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ COMMANDS /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
CC = cc
RM = rm -rf

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ FLAGS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
CFLAGS 	= -Wall -Werror -Wextra
MK_FLAG = --no-print-directory
LFLAGS 	= -L ./libft -lft -L ./mlx -lmlx -lXext -lX11 -lm -lbsd

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ PATHS _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
INC		= includes
SRC_DIR		= srcs
OBJ_DIR		= objs
MAP_DIR		= maps

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ FILES _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
NAME 		= so_long
LIBFT		= libft/libft.a
MLX		= mlx/libmlx.a
MAP		= screen.ber
FILES 		= checker clean main map move render init
SRC 		= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

# /\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_ RULES _/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\ #
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME) -I $(INC)
	@echo "$(NAME) created"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c 
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "so_long objs directory created"

$(MLX):
	@make $(MK_FLAG) -sC mlx
	@echo "libmlx.a created"

$(LIBFT):
	@make $(MK_FLAG) -C ./libft

clean:
	@$(RM) $(OBJ_DIR)
	@make $(MK_FLAG) -C ./libft clean
	@make $(MK_FLAG) -C ./mlx clean
	@echo "objs removed"

fclean: clean
	@$(RM) $(NAME) $(LIBFT)
	@echo "$(NAME) and $(LIBFT) removed"

re: fclean all

# valgrind --leak-check=full -s --show-leak-kinds=all --track-origins=yes

test: re
	@valgrind --leak-check=full -s --show-leak-kinds=all --track-origins=yes ./$(NAME) "$(MAP_DIR)/$(MAP)"

.PHONY: all clean fclean re test

.SILENT:
