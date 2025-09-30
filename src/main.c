/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:52:39 by nmikuka           #+#    #+#             */
/*   Updated: 2025/09/30 18:59:27 by nmikuka          ###   ########.fr       */
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
	draw(game);
	// ft_createhooks(&game);
	// ft_init_images(&game);
	// ft_fill_tilemap(&game);
	// ft_update_count(&game);
	mlx_loop(game->mlx);
	// ft_exit_error("MiniLibX looping error.\n", &game);
	ft_clean();
	return (0);
}
