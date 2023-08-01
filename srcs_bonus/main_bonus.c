/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:26:28 by damachad          #+#    #+#             */
/*   Updated: 2023/08/01 14:44:59 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

// Test nbr of arguments and mapfile extension

int	main(int argc, char **argv)
{
	if (argc != 2)
		error_msg(NULL, "Usage: ./so_long <mapfile>\n");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4))
		error_msg(NULL, "Invalid map file extension\n");
	start_game(argv[1]);
	return (0);
}
