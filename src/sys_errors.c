/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/26 14:07:06 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_clean()
{
	t_gs	*game;

	game = ft_game();
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
	t_gs	*game;

	game = ft_game();
	ft_print(COLOR_R "Error\n" COLOR_Y);
	perror(str);
	ft_print("" COLOR_X);
	ft_clean(game);
	exit(EXIT_FAILURE);
}

void	ft_exit(char *str)
{
	t_gs	*game;

	game = ft_game();
	ft_print(COLOR_R "Error\n" COLOR_Y);
	ft_print(str);
	ft_print("" COLOR_X);
	ft_clean(game);
	exit(EXIT_FAILURE);
}
