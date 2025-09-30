/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/30 14:33:59 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_clean(t_gs *game)
{
	// t_gs	*game;

	// game = ft_game();
	if (game->mlx)
	{
		// mlx_destroy_window(game->mlx, game->window);
		free(game->mlx);
	}
	// if (game->enemies)
	// 	free(game->enemies);
	// if (game->collects)
	// 	free(game->collects);
	// ft_free_map(&game->map);
	// ft_print(COLOR_B "Exiting\n" COLOR_X);
	// system("leaks -list so_long");
	// ft_print("\n");
}

void	ft_exit_error(char *str)
{
	printf(COLOR_R "Error\n" COLOR_Y);
	perror(str);
	printf("" COLOR_X);
	ft_clean();
	exit(EXIT_FAILURE);
}

void	ft_exit(char *str)
{
	printf(COLOR_R "Error\n" COLOR_Y);
	printf("%s"COLOR_X, str);
	ft_clean();
	exit(EXIT_FAILURE);
}
