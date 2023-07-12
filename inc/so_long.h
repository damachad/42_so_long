/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:19:49 by damachad          #+#    #+#             */
/*   Updated: 2023/07/12 15:27:10 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./inc_mlx/mlx.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>

# define WIDTH 600
# define HEIGHT 600
# define COLOR 0x000000
# define WHITE 0xFFFFFF

typedef struct s_point
{
	unsigned int	x;
	unsigned int	y;
}					t_point;

typedef struct s_map
{
	char			**bytes;
	unsigned int	columns;
	unsigned int	rows;
	unsigned int	collect;
	unsigned int	exits;
	unsigned int	players;
}					t_map;

typedef struct s_sprite{
	void	*img;
	int		width;
	int		height;
}			t_sprite;

typedef struct s_img
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

typedef struct s_game
{
	t_map			*map;	
	t_point			curr;
	t_point			next;
	t_img			display;
	t_sprite		*sprites;
	unsigned int	collect;
	unsigned int	moves;
}					t_game;

int		nr_lines(t_game *game, char *mapfile);
void	map_print(t_map *map);
void	load_map(t_game *game, char *mapfile);
t_map	*new_map(unsigned int columns, unsigned int rows);

void	destroy_game(t_game *game);
void	free_matrix(char **bytes);
void	destroy_map(t_map *map);
void	error_msg(t_game *game, char *msg);

bool	is_rectangle(t_map *map);
bool	is_bordered(t_map *map);
void	validate_map(t_game *game);

#endif