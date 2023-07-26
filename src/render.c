/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:13:08 by damachad          #+#    #+#             */
/*   Updated: 2023/07/26 15:10:09 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

// Render graphics according to map

void	put_tile(t_game *game, t_point point)
{
	t_sprite	sprite;

	if (game->map->bytes[point.y][point.x] == '1')
		sprite = game->sprites[1];
	else if (game->map->bytes[point.y][point.x] == 'C')
		sprite = game->sprites[2];
	else if (game->map->bytes[point.y][point.x] == 'E')
		sprite = game->sprites[3];
	else if (game->map->bytes[point.y][point.x] == 'P')
		sprite = game->sprites[4];
	else if (game->map->bytes[point.y][point.x] == '0')
		sprite = game->sprites[0];
	mlx_put_image_to_window(game->display.mlx, game->display.win, sprite.img, point.x * sprite.width, point.y * sprite.height);
}

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

int	render_frame(t_game *game)
{
	if (!is_valid_movement(game))
		return (0);
	ft_putstr_fd("Number of movements: ", STDOUT_FILENO);
	ft_putnbr_fd(++game->moves, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (at(game, game->next) == 'C')
		game->collect++;
	else if (at(game, game->next) == 'E' && game->collect == game->map->collect)
		quit_prog(game);
	move_player(game);
	return (0);
}