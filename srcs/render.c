/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:13:08 by damachad          #+#    #+#             */
/*   Updated: 2023/08/01 12:27:56 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Print error message

void	error_msg(t_game *game, char *msg)
{
	destroy_game(game);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

// Render graphics according to map
// Put image according to nbr of pixels in tile

void	put_tile(t_game *g, t_point p)
{
	t_sprite	sp;

	if (g->map->bytes[p.y][p.x] == '1')
		sp = g->sprites[1];
	else if (g->map->bytes[p.y][p.x] == 'C')
		sp = g->sprites[2];
	else if (g->map->bytes[p.y][p.x] == 'E')
		sp = g->sprites[3];
	else if (g->map->bytes[p.y][p.x] == 'P')
		sp = g->sprites[4];
	else if (g->map->bytes[p.y][p.x] == '0')
		sp = g->sprites[0];
	mlx_put_image_to_window(g->mlx, g->win, sp.img, \
	p.x * sp.width, p.y * sp.height);
}

// Run over map and render each tile, using the put_tile function

void	render_map(t_game *game)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->columns)
		{
			put_tile(game, (t_point){x, y});
			x++;
		}
		y++;
	}
}

// Render the frame, update nbr of movements and collectibles 
// and check if the game is over

int	render_frame(t_game *game)
{
	if (!is_valid_movement(game))
		return (0);
	ft_putstr_fd("Movement counter: ", 1);
	ft_putnbr_fd(++game->moves, 1);
	ft_putchar_fd('\n', 1);
	if (entity_at(game, game->next) == 'C')
	{
		game->collected++;
		if (game->collected == game->map->collect)
			game->can_exit = true;
	}
	if (entity_at(game, game->next) == 'E' && game->can_exit == true)
		quit_prog(game);
	move_player(game);
	return (0);
}
