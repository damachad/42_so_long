/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:02:32 by damachad          #+#    #+#             */
/*   Updated: 2023/07/12 15:30:01 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/so_long.h"

bool	is_rectangle(t_map *map)
{
	unsigned int	i;
	unsigned int	lenght;

	i = 0;
	lenght = ft_strlen(map->bytes[0]);
	while (i < map->rows)
		if (ft_strlen(map->bytes[i++]) != lenght)
			return (false);
	map->columns = lenght;
	return (true);
}

bool	is_bordered(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->rows)
	{
		if (map->bytes[i][0] != 1 || map->bytes[i][map->columns - 1] != 1)
			return (false);
		i++;
	}
	i = 0;
	while (i < map->columns)
	{
		if (map->bytes[0][i] != 1 || map->bytes[map->rows - 1][i] != 1)
			return (false);
		i++;
	}
	return (true);
}

void	validate_map(t_game *game)
{
	if (game->map->rows == 0)
		error_msg(game, "Map is empty.\n");
	if (!is_rectangle(game->map))
		error_msg(game, "Map is not rectangular.\n");
	if (!is_bordered(game->map))
		error_msg(game, "Map is not completely surrounded by walls.\n");
	// if (!has_valid_entities(game))
	// 	error_msg(game, "Map has invalid entities.\n");
	// if (!has_valid_path(game))
	// 	error_msg(game, "Map has not a traversable path to end the level.\n");
}
