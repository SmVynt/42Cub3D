/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:52:39 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/03 17:20:04 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_gs	*game;

	ft_initialize();
	ft_checkinput(argc, argv);
	ft_setgame();
	game = ft_game();
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	if (!game->mlx)
		ft_exit_error("Could not initialize MiniLibX\n");
	printf(COLOR_G"MiniLibX initialized!\n"COLOR_X);
	ft_createhooks();
	draw(game);
	mlx_loop(game->mlx);
	ft_exit();
	// ft_exit_error("MiniLibX looping error.\n");
	return (0);
}
