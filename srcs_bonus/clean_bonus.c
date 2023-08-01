/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:43:13 by damachad          #+#    #+#             */
/*   Updated: 2023/08/01 15:12:18 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

// Calls function to free resources and exits program
// Called when game is over

int	quit_prog(t_game *game)
{
	destroy_game(game);
	exit(EXIT_SUCCESS);
}

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

// Destroy *img of every sprite and free *sprites

void	destroy_sprites(t_game *game)
{
	unsigned int	i;

	i = 0;
	while (i < NUM_SPRITES)
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

// Free all used resources

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
