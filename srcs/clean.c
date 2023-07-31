/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:43:13 by damachad          #+#    #+#             */
/*   Updated: 2023/07/31 16:03:50 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_matrix(char **bytes)
{
	unsigned int	i;

	i = 0;
	if (!bytes)
		return ;
	while (bytes[i])
		free(bytes[i++]);
	free(bytes);
}

// Destroy *img of every sprite (5) and free *sprites

void	destroy_sprites(t_game *game)
{
	unsigned int	i;

	i = 0;
	while (i < 5)
		mlx_destroy_image(game->mlx, game->sprites[i++].img);
	free(game->sprites);
}

void	destroy_map(t_map *map)
{
	if (!map)
		return ;
	free_matrix(map->bytes);
	free(map);
}

void	destroy_game(t_game *game)
{
	if (!game)
		return ;
	if (game->sprites)
		destroy_sprites(game);
	if (game->map)
		destroy_map(game->map);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}

// Print error message

void	error_msg(t_game *game, char *msg)
{
	destroy_game(game);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(1);
}
