/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:52:39 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/11 15:05:45 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_gs	*game;

	ft_initialize();
	ft_checkinput(argc, argv);
	game = ft_game();
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	if (!game->mlx)
		ft_exit_error("Could not initialize MiniLibX\n");
	printf(COLOR_G"MiniLibX initialized!\n"COLOR_X);
	ft_createhooks();
	ft_setgame();
	draw(WIDTH, HEIGHT, game);
	mlx_loop(game->mlx);
	ft_exit();
	return (0);
}
