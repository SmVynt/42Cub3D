/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:52:39 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/30 10:29:54 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_gs	*game;

	ft_checkinput (argc, argv);
	game = ft_game();
	// ft_initialize (game, argv);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	if (!game->mlx)
		ft_exit_error("Could not initialize MiniLibX\n");
	draw(game);
	// ft_createhooks(&game);
	// ft_init_images(&game);
	// ft_fill_tilemap(&game);
	// ft_update_count(&game);
	mlx_loop(game->mlx);
	// ft_exit_error("MiniLibX looping error.\n", &game);
	return (0);
}
