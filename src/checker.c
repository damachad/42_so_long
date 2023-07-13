/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:02:32 by damachad          #+#    #+#             */
/*   Updated: 2023/07/13 16:47:35 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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
		if (map->bytes[i][0] != '1' || map->bytes[i][map->columns - 1] != '1')
			return (false);
		i++;
	}
	i = 0;
	while (i < map->columns)
	{
		if (map->bytes[0][i] != '1' || map->bytes[map->rows - 1][i] != '1')
			return (false);
		i++;
	}
	return (true);
}

bool	exit_true(t_map *map, t_point current, char **dup_map)
{
	static unsigned int	collectibles;
	static bool			found_exit;

	if (dup_map[current.y][current.x] == '1')
		return (false);
	else if (dup_map[current.y][current.x] == 'C')
		collectibles++;
	else if (dup_map[current.y][current.x] == 'E')
		found_exit = true;
	dup_map[current.y][current.x] = '1';
	exit_true(map, (t_point){current.x + 1, current.y}, dup_map);
	exit_true(map, (t_point){current.x - 1, current.y}, dup_map);
	exit_true(map, (t_point){current.x, current.y + 1}, dup_map);
	exit_true(map, (t_point){current.x, current.y - 1}, dup_map);
	return (collectibles == map->collect && found_exit);
}

bool	valid_path(t_game *game)
{
	char			**dup_map;
	bool			valid;
	unsigned int	i;

	i = 0;
	dup_map = ft_calloc(game->map->rows + 1, sizeof(char *));
	if (!dup_map)
		error_msg(game, "Failed allocation 1 on valid_path()\n");
	while (i < game->map->rows)
	{
		dup_map[i] = ft_strdup(game->map->bytes[i]);
		if (!dup_map[i])
		{
			free_matrix(dup_map);
			error_msg(game, "Failed allocation 2 on valid_path()\n");
		}
		i++;
	}
	valid = exit_true(game->map, game->curr, dup_map);
	free_matrix(dup_map);
	return (valid);
}

void	validate_map(t_game *game)
{
	if (game->map->rows == 0)
		error_msg(game, "Map is empty.\n");
	if (!is_rectangle(game->map))
		error_msg(game, "Map is not rectangular.\n");
	if (!is_bordered(game->map))
		error_msg(game, "Map is not completely surrounded by walls.\n");
	if (!load_components(game))
	 	error_msg(game, "Map has invalid number of components.\n");
	if (!valid_path(game))
	 	error_msg(game, "Map has no viable path to all 'C's and/or to the exit.\n");
	map_print(game->map);
}
