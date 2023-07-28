/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:19:49 by damachad          #+#    #+#             */
/*   Updated: 2023/07/28 12:02:29 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>

#define FLOOR "images/floor.xpm"
#define WALL "images/wall.xpm"
#define COLLECT "images/collect.xpm"
#define EXIT "images/exit.xpm"
#define PLAYER "images/player.xpm"

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

typedef struct s_graphs
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}			t_graphs;

typedef struct s_game
{
	t_map			*map;	
	t_point			curr;
	t_point			next;
	t_graphs			display;
	t_sprite		*sprites;
	unsigned int	collect;
	unsigned int	moves;
	bool			can_exit;
}					t_game;

/*--------------------------map--------------------------*/
int		nr_lines(t_game *game, char *mapfile);
void	load_map(t_game *game, char *mapfile);
t_map	*new_map(unsigned int columns, unsigned int rows);
bool	load_components(t_game *g);

/*-------------------------clean-------------------------*/
void	destroy_game(t_game *game);
void	free_matrix(char **bytes);
void	destroy_map(t_map *map);
void	error_msg(t_game *game, char *msg);
void	destroy_sprites(t_game *g);

/*------------------------checker------------------------*/
bool	is_rectangle(t_map *map);
bool	is_bordered(t_map *map);
void	validate_map(t_game *game);
bool	exit_true(t_map *map, t_point current, char **dup_map);

/*-------------------------start-------------------------*/
void	init_graphics(t_game *game);
void	start_game(char	*mapfile);
void	load_sprites(t_game *game);
int	handle_keypress(int keysym, t_game *game);
int	quit_prog(t_game *game);

/*-------------------------render-------------------------*/
void	put_tile(t_game *game, t_point point);
void	render_map(t_game *game);
int		render_frame(t_game *game);

/*--------------------------move--------------------------*/
char	at(t_game *g, t_point p);
bool	is_same_point(t_point p1, t_point p2);
bool	is_valid_movement(t_game *g);
void	move_player(t_game *g);

#endif