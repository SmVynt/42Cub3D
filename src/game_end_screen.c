/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:33:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/10 20:56:43 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_centered_image(mlx_t *mlx, mlx_texture_t *tex)
{
	int32_t			x;
	int32_t			y;
	mlx_image_t		*img;

	img = ft_game()->end_screen;
	draw_ui_img(img, tex);
	x = (ft_game()->view3d->width - img->width) / 2;
	y = (ft_game()->view3d->height - img->height) / 2;
	x = ft_clamp(x, 0, ft_game()->view3d->width);
	y = ft_clamp(y, 0, ft_game()->view3d->height);
	if (mlx_image_to_window(mlx, img, x, y) < 0)
	{
		ft_exit_perror("Failed to put image to window\n");
		mlx_delete_image(mlx, img);
		ft_game()->end_screen = NULL;
	}
}

void	show_end_screen(void)
{
	t_gs	*game;
	int		width;
	int		height;

	game = ft_game();
	if (!game->game_over)
		return ;
	if (game->view3d->height > game->view3d->width / 2)
	{
		width = game->view3d->width / 2;
		height = width / 2;
	}
	else
	{
		height = game->view3d->height / 2;
		width = height * 2;
	}
	game->end_screen = mlx_new_image(game->mlx, width, height);
	if (!game->end_screen)
		return ;
	if (game->game_over == 1)
		load_centered_image(game->mlx, game->textures.screen_victory);
	else if (game->game_over == -1)
		load_centered_image(game->mlx, game->textures.screen_defeat);
}
