/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:58:31 by damachad          #+#    #+#             */
/*   Updated: 2023/07/13 17:44:32 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	init_graphics(t_game *game)
{
	game->display.mlx = mlx_init();
	if (!game->display.mlx)
		error_msg(game, "mlx_init() failed\n");
	game->display.win = mlx_new_window(game->display.mlx, game->map->columns * 64, \
	game->map->rows * 64, "so_long"); //why 64?
	if (!game->display.win)
		error_msg(game, "mlx_new_window() failed\n");
}

void	start_game(char	*mapfile)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	load_map(&game, mapfile);
	validate_map(&game);
	init_graphics(&game);
	load_sprites(&game);
	render_map(&game);
	mlx_loop(game.display.mlx);
}

void	load_sprites(t_game *game)
{
	game->sprites = ft_calloc(5, sizeof(t_sprite));
	if (!game->sprites)
		error_msg(game, "Could not allocate memory for sprites.\n");
	game->sprites[0].img = mlx_xpm_file_to_image(game->display.mlx, \
	FLOOR, &(game->sprites[0].width), &(game->sprites[0].height));
	game->sprites[1].img = mlx_xpm_file_to_image(game->display.mlx, \
	WALL, &(game->sprites[1].width), &(game->sprites[1].height));
	game->sprites[2].img = mlx_xpm_file_to_image(game->display.mlx, \
	COLLECT, &(game->sprites[2].width), &(game->sprites[2].height));
	game->sprites[3].img = mlx_xpm_file_to_image(game->display.mlx, \
	EXIT, &(game->sprites[3].width), &(game->sprites[3].height));
	game->sprites[4].img = mlx_xpm_file_to_image(game->display.mlx, \
	PLAYER, &(game->sprites[4].width), &(game->sprites[4].height));
}