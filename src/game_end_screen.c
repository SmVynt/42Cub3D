/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:33:42 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/10 02:36:28 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_end_screen_textures(void)
{
	t_gs		*game;

	game = ft_game();
	ft_load_texture(TEX_VICTORY, &game->textures.screen_victory);
	ft_load_texture(TEX_DEFEAT, &game->textures.screen_defeat);
}

static void	draw_end_screen(mlx_texture_t *tex)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	x_tex;
	uint32_t	y_tex;
	double		win_scale;

	win_scale = ft_game()->end_screen->width
		/ (double)ft_game()->textures.screen_victory->width;
	x = UI_PIXEL_SIZE / 2;
	while (x < tex->width * win_scale)
	{
		y = UI_PIXEL_SIZE / 2;
		x_tex = (int)round(x / win_scale);
		while (y < tex->height * win_scale)
		{
			y_tex = (int)round(y / win_scale);
			draw_square(ft_game()->end_screen, UI_PIXEL_SIZE, (t_point){x, y},
				ft_get_pixel_color(tex, (t_point){x_tex, y_tex}));
			y += UI_PIXEL_SIZE;
		}
		x += UI_PIXEL_SIZE;
	}
}

static void	load_centered_image(mlx_t *mlx, mlx_texture_t *tex)
{
	int32_t			x;
	int32_t			y;
	mlx_image_t		*img;

	img = ft_game()->end_screen;
	draw_end_screen(tex);
	x = ft_clamp((ft_game()->view3d->width - img->width) / 2, 0,
			ft_game()->view3d->width);
	y = ft_clamp((ft_game()->view3d->height - img->height) / 2, 0,
			ft_game()->view3d->height);
	if (mlx_image_to_window(mlx, img, x, y) < 0)
	{
		fprintf(stderr, "Error: failed to put image to window\n");
		mlx_delete_image(mlx, img);
		ft_game()->end_screen = NULL;
	}
}

void	show_end_screen(void)
{
	t_gs	*game;

	game = ft_game();
	if (!game->game_over)
		return ;
	ft_game()->end_screen = mlx_new_image(ft_game()->mlx,
		ft_game()->view3d->width / 2, ft_game()->view3d->width / 4);
	if (game->game_over == 1)
		load_centered_image(ft_game()->mlx, ft_game()->textures.screen_victory);
	else if (game->game_over == -1)
		load_centered_image(ft_game()->mlx, ft_game()->textures.screen_defeat);
}
