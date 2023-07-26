/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:43:13 by damachad          #+#    #+#             */
/*   Updated: 2023/07/25 11:39:52 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	destroy_game(t_game *game)
{
	if (!game)
		return ;
	if (game->sprites)
		destroy_sprites(game);
	if (game->display.img)
		mlx_destroy_image(game->display.mlx, game->display.img);
	if (game->display.win)
		mlx_destroy_window(game->display.mlx, game->display.win);
	if (game->display.mlx)
		mlx_destroy_display(game->display.mlx);
	if (game->map)
		destroy_map(game->map);
	free(game->display.mlx);
}

void	free_matrix(char **bytes)
{	
	size_t	i;

	i = 0;
	if (!bytes)
		return ;
	while (bytes[i])
		free(bytes[i++]);
	free(bytes);
}

void	destroy_sprites(t_game *g)
{
	int	i;

	i = 0;
	while (i < 5)
		mlx_destroy_image(g->display.mlx, g->sprites[i++].img);
	free(g->sprites);
}

void	destroy_map(t_map *map)
{
	if (!map)
		return ;
	free_matrix(map->bytes);
	free(map);
}

void	error_msg(t_game *game, char *msg)
{
	destroy_game(game);
	ft_putstr_fd("\nError. ", 2);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}