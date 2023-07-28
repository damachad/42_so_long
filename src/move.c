/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:13:11 by damachad          #+#    #+#             */
/*   Updated: 2023/07/28 12:14:34 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	at(t_game *g, t_point p)
{
	return (g->map->bytes[p.y][p.x]);
}

bool	is_same_point(t_point p1, t_point p2)
{
	return (p1.x == p2.x && p1.y == p2.y);
}

bool	is_valid_movement(t_game *g)
{
	bool is_valid;

	if (at(g, g->next) != '1')
		is_valid = true;
	if (g->can_exit == false && at(g, g->next) == 'E')
		is_valid = false;
	return (!is_same_point(g->curr, g->next) && is_valid);
}

void	move_player(t_game *g)
{
	static char	previous = '0';

	g->map->bytes[g->curr.y][g->curr.x] = previous;
	if (at(g, g->next) != 'C')
		previous = g->map->bytes[g->next.y][g->next.x];
	else
		previous = '0';
	g->map->bytes[g->next.y][g->next.x] = 'P';
	put_tile(g, (t_point){g->curr.x, g->curr.y});
	put_tile(g, (t_point){g->next.x, g->next.y});
	g->curr = g->next;
}
