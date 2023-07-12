/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:26:28 by damachad          #+#    #+#             */
/*   Updated: 2023/07/12 15:24:32 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nWrong number of arguments\n");
		return (5);
	}
	else
	{
		ft_bzero(&game, sizeof(t_game));
		load_map(&game, argv[1]);
		validate_map(&game);
	}
	return (0);
}