/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:13:11 by damachad          #+#    #+#             */
/*   Updated: 2023/08/01 14:45:06 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

// Returns entity (character) of the map at given point

char	entity_at(t_game *game, t_point point)
{
	return (game->map->bytes[point.y][point.x]);
}

// Evaluates if two points have the same coordinates

bool	is_same_point(t_point p1, t_point p2)
{
	return (p1.x == p2.x && p1.y == p2.y);
}

// Evaluates if movemente is valid by checking if the
// next point the player intends to move is a wall or
// the exit (before getting all collectibles)
// Checks if the next and current point are the same,
// which is true in the beginning of the game

bool	is_valid_movement(t_game *game)
{
	bool	is_valid;

	is_valid = false;
	if (entity_at(game, game->next) != '1')
		is_valid = true;
	if (game->can_exit == false && entity_at(game, game->next) == 'E')
		is_valid = false;
	return (!is_same_point(game->curr, game->next) && is_valid);
}

// Handle keypresses, and exit if 'ESC' is pressed (events)
// Changes the point where the player will move to

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		quit_prog(game);
	else if (keysym == XK_w)
		game->next = (t_point){game->curr.x, game->curr.y - 1};
	else if (keysym == XK_a)
		game->next = (t_point){game->curr.x - 1, game->curr.y};
	else if (keysym == XK_s)
		game->next = (t_point){game->curr.x, game->curr.y + 1};
	else if (keysym == XK_d)
		game->next = (t_point){game->curr.x + 1, game->curr.y};
	return (keysym);
}

// "Moves" the player, by putting a floor tile in the position
// the player was and the player tile in the position the player
// went. Then the 'current' position is updated.

void	move_player(t_game *g)
{
	g->map->bytes[g->curr.y][g->curr.x] = '0';
	g->map->bytes[g->next.y][g->next.x] = 'P';
	put_tile(g, (t_point){g->curr.x, g->curr.y});
	put_tile(g, (t_point){g->next.x, g->next.y});
	g->curr = g->next;
}
