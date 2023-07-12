# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damachad <damachad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 10:57:36 by damachad          #+#    #+#              #
#    Updated: 2023/07/12 14:28:13 by damachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(INC) -I$(INC_MLX)
INC = inc
INC_MLX = inc/inc_mlx
LFLAGS = -L./libft -lft -L./mlx -lmlx -lXext -lX11 -lm -lbsd
LIBFT = libft/libft.a
RM = rm -f
NAME = map
MAP_PATH = maps/valid1.ber
SRC_PATH = src
BIN_PATH = bin
SRC = $(wildcard $(SRC_PATH)/*.c) # write src manually
OBJ = $(SRC:$(SRC_PATH)%.c=$(SRC_PATH)%.o)
BIN_OBJ = $(SRC:$(SRC_PATH)%.c=$(BIN_PATH)/%.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@mv $(OBJ) $(BIN_PATH)
	@echo "objs moved to bin"
	@$(CC) $(BIN_OBJ) $(LFLAGS) -o $(NAME)
	@echo "$(NAME) created"

$(LIBFT):
	@make -C ./libft

clean:
	@$(RM) $(BIN_OBJ)
	@make -C ./libft clean
	@echo "objs removed"

fclean: clean
	@$(RM) $(NAME) $(LIBFT)
	@echo "$(NAME) removed"

re: fclean all

# valgrind --leak-check=full -s --show-leak-kinds=all 
test: re
	@./$(NAME) "$(MAP_PATH)"

debug:
	@$(CC) -g $(SRC) $(LFLAGS) -o $(NAME)
	@gdb --args $(NAME) "$(MAP_PATH)"

.PHONY: all clean fclean re test
