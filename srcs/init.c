/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:58:31 by damachad          #+#    #+#             */
/*   Updated: 2023/08/02 15:09:17 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Initialize graphics using mlx_init() and mlx_new_window()
// 32 is the size of the sprites (tiles)

void	init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_msg(game, "mlx_init() failed\n");
	game->win = mlx_new_window(game->mlx, game->map->columns * 32, \
	game->map->rows * 32, "so_long");
	if (!game->win)
		error_msg(game, "mlx_new_window() failed\n");
}

// Initialize 't_game' struct, load and check map,
// initialize graphics, load sprites, render map,
// and start game loop

void	start_game(char	*mapfile)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	game.can_exit = false;
	load_map(&game, mapfile);
	validate_map(&game);
	init_graphics(&game);
	load_sprites(&game);
	render_map(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
	mlx_hook(game.win, DestroyNotify, KeyPressMask, quit_prog, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
}

// Load sprites from xpm files (defined in macros) using mlx_xpm_file_to_image()

void	load_sprites(t_game *game)
{
	game->sprites = malloc(5 * sizeof(t_sprite));
	if (!game->sprites)
		error_msg(game, "Could not allocate memory for sprites.\n");
	game->sprites[0].img = mlx_xpm_file_to_image(game->mlx, \
	FLOOR, &(game->sprites[0].width), &(game->sprites[0].height));
	game->sprites[1].img = mlx_xpm_file_to_image(game->mlx, \
	WALL, &(game->sprites[1].width), &(game->sprites[1].height));
	game->sprites[2].img = mlx_xpm_file_to_image(game->mlx, \
	COLLECT, &(game->sprites[2].width), &(game->sprites[2].height));
	game->sprites[3].img = mlx_xpm_file_to_image(game->mlx, \
	EXIT, &(game->sprites[3].width), &(game->sprites[3].height));
	game->sprites[4].img = mlx_xpm_file_to_image(game->mlx, \
	PLAYER, &(game->sprites[4].width), &(game->sprites[4].height));
}
