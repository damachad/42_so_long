/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:31:17 by damachad          #+#    #+#             */
/*   Updated: 2023/07/11 15:01:22 by damachad         ###   ########.fr       */
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

int	map_lines(char *mapfile)
{
	int		fd;
	int		lines;
	char	*tmp;

	lines = 0;
	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		exit (8);
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
	game->map = new_map(0, map_lines(mapfile));
	if (!game->map)
		exit (9);
	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		exit (2);
	while (i < game->map->rows)
	{
		line = get_next_line(fd);
		if (!line)
			exit (3);
		game->map->bytes[i] = ft_strtrim(line, "\n");
		if (!game->map->bytes[i++])
			exit (4);
		free(line);
	}
	close(fd);
	map_print(game->map);
}


void	map_print(t_map *map)
{
	unsigned int	i;

	i = 0;
	printf("Length: %u\n", map->columns);
	printf("Width: %u\n", map->rows);
	printf("Players: %u\n", map->players);
	printf("Exits: %u\n", map->exits);
	printf("Coins: %u\n", map->collect);
	while (i < map->rows)
		printf("%s\n", map->bytes[i++]);
}
