/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:31:17 by damachad          #+#    #+#             */
/*   Updated: 2023/08/02 15:27:01 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Allocate memory for map, with nbr of rows as nbr of
// strings in '**bytes'. Null pointer at the end in case
// free_matrix needs to be called

t_map	*new_map(unsigned int columns, unsigned int rows)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->bytes = ft_calloc(rows + 1, sizeof(char *));
	if (!map->bytes)
	{
		free(map);
		return (NULL);
	}
	map->columns = columns;
	map->rows = rows;
	return (map);
}

// Count nbr of lines in mapfile

int	nr_lines(t_game *game, char *mapfile)
{
	int		fd;
	int		lines;
	char	*tmp;

	lines = 0;
	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		error_msg(game, "Could not open map file.\n");
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		lines++;
		free(tmp);
	}
	close(fd);
	return (lines);
}

// Load map from file into '**bytes', removing the
// '\n' at the end of each line

void	load_map(t_game *game, char *mapfile)
{
	int					fd;
	char				*line;
	unsigned int		i;

	i = 0;
	game->map = new_map(0, nr_lines(game, mapfile));
	if (!game->map)
		error_msg(game, "Could not allocate memory for map.\n");
	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		error_msg(game, "Could not open map file.\n");
	while (i < game->map->rows)
	{
		line = get_next_line(fd);
		if (!line)
			error_msg(game, "Could not read map file.\n");
		game->map->bytes[i] = ft_strtrim(line, "\n");
		if (!game->map->bytes[i++])
			error_msg(game, "Could not trim line.\n");
		free(line);
	}
	close(fd);
}

// Load nbr of each entity to map struct

void	assign_entities(t_game *g, char entity)
{
	if (entity == 'C')
		g->map->collect++;
	else if (entity == 'P')
		g->map->players++;
	else if (entity == 'E')
		g->map->exits++;
}

// Check valid entities and set beginning position of player

bool	load_components(t_game *g)
{
	unsigned int	row;
	unsigned int	col;

	row = 0;
	while (row < g->map->rows)
	{
		col = 0;
		while (col < g->map->columns)
		{
			if (!ft_strchr("01CEP", g->map->bytes[row][col]))
				return (false);
			assign_entities(g, g->map->bytes[row][col]);
			if (g->map->bytes[row][col] == 'P')
			{
				g->curr = (t_point){col, row};
				g->next = g->curr;
			}
			col++;
		}
		row++;
	}
	return (g->map->players == 1 && g->map->exits == 1 && g->map->collect > 0);
}
