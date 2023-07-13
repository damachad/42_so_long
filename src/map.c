/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:31:17 by damachad          #+#    #+#             */
/*   Updated: 2023/07/13 15:42:37 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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

int	nr_lines(t_game *game, char *mapfile)
{
	int		fd;
	int		lines;
	char	*tmp;

	lines = 0;
	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		error_msg(game, "Could not open file.\n");
	while (1) //infinite loop
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
		error_msg(game, "Could not open file.\n");
	while (i < game->map->rows)
	{
		line = get_next_line(fd);
		if (!line)
			error_msg(game, "Could not read file.\n");
		game->map->bytes[i] = ft_strtrim(line, "\n");
		if (!game->map->bytes[i++])
			error_msg(game, "Could not trim line.\n");
		free(line);
	}
	close(fd);
	map_print(game->map);
}

bool	load_components(t_game *g)
{
	unsigned int	row;
	unsigned int	col;

	row = -1;
	while(++row < g->map->rows)
	{
		col = -1;
		while (++col < g->map->columns)
		{
			if (g->map->bytes[row][col] == 'C')
				g->map->collect++;
			else if (g->map->bytes[row][col] == 'P')
			{
				g->map->players++;
				g->curr = (t_point){col, row};
				g->next = g->curr;
			}
			else if (g->map->bytes[row][col] == 'E')
				g->map->exits++;
			else if (!ft_strchr("01", g->map->bytes[row][col]))
				return (false);
		}
	}
	return (g->map->players == 1 && g->map->exits == 1 && g->map->collect > 0);
}

void	map_print(t_map *map)
{
	unsigned int	i;

	i = 0;
	printf("Length: %u\n", map->columns);
	printf("Width: %u\n", map->rows);
	printf("Collectibles: %u\n", map->collect);
	printf("Exits: %u\n", map->exits);
	printf("Players: %u\n", map->players);
	printf("Bytes:\n");
	while (i < map->rows)
		printf("%s\n", map->bytes[i++]);
}
