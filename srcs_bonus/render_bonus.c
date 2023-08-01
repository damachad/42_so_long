/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:13:08 by damachad          #+#    #+#             */
/*   Updated: 2023/08/01 15:50:21 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

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
	else if (g->map->bytes[p.y][p.x] == 'H')
		sp = g->sprites[5];
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

int	render_frame(t_game *g)
{
	if (!is_valid_movement(g))
		return (0);
	ft_putstr_fd("Movement counter: ", 1);
	ft_putnbr_fd(++g->moves, 1);
	ft_putchar_fd('\n', 1);
	if (entity_at(g, g->next) == 'C')
	{
		g->collected++;
		if (g->collected == g->map->collect)
			g->can_exit = true;
	}
	if (entity_at(g, g->next) == 'E' && g->can_exit == true)
	{
		ft_putstr_fd("\nYou Won!\n\n", 1);
		quit_prog(g);
	}
	if (entity_at(g, g->next) == 'H')
	{
		ft_putstr_fd("\nGame Over!\n\n", 1);
		quit_prog(g);
	}
	move_player(g);
	return (0);
}
