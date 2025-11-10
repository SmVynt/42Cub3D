/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/10 16:56:31 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ui_minimap(void)
{
	uint32_t		x;
	uint32_t		y;
	uint32_t		x_tex;
	uint32_t		y_tex;
	mlx_texture_t	*bg;
	double			win_scale;

	win_scale = (double)(ft_game()->view3d->height / (double)HEIGHT * UI_SCALE);
	bg = ft_game()->textures.ui_minimap;
	x = 0;
	while (x < bg->width * win_scale)
	{
		y = 0;
		x_tex = x / win_scale;
		while (y < bg->height * win_scale)
		{
			y_tex = y / win_scale;
			draw_square(ft_game()->minimap, UI_PIXEL_SIZE, (t_point){x, y},
				ft_get_pixel_color(bg, (t_point){x_tex, y_tex}));
			y += UI_PIXEL_SIZE;
		}
		x += UI_PIXEL_SIZE;
	}
}

void	ft_update_hp_bar(void)
{
	mlx_image_t	*image;
	int			i;
	int			j;
	t_point		offset;

	image = ft_game()->health_bar;
	memset(image->pixels, 0, image->width * image->height * sizeof(int32_t));
	offset.u = round((float)image->width * (1 - UI_HP_BAR_XSCALE)) / 2;
	offset.v = round((float)image->height * (1 - UI_HP_BAR_YSCALE)) / 2;
	i = offset.u;
	while (i < round((float)((image->width - offset.u) * ft_game()->player->hp) / MAX_HP))
	{
		j = offset.v;
		while (j < round(image->height - offset.v))
		{
			draw_square(image, UI_PIXEL_SIZE, (t_point){i, j}, UI_COLOR_HP);
			j += UI_PIXEL_SIZE;
		}
		i += UI_PIXEL_SIZE;
	}
}

void	draw_ui_health(void)
{
	uint32_t		x;
	uint32_t		y;
	uint32_t		x_tex;
	uint32_t		y_tex;
	mlx_texture_t	*bg;
	float			win_scale;

	win_scale = (float)ft_game()->view3d->height / HEIGHT * (float)UI_SCALE;
	bg = ft_game()->textures.ui_health;
	x = 0;
	while (x < bg->width * win_scale)
	{
		y = 0;
		x_tex = x / win_scale;
		while (y < bg->height * win_scale)
		{
			y_tex = y / win_scale;
			put_pixel(ft_game()->health, x, y, ft_get_pixel_color(bg, (t_point){x_tex, y_tex}));
			y++;
		}
		x++;
	}
}

void	draw_ui_img(mlx_image_t *img, mlx_texture_t *tex)
{
	uint32_t		x;
	uint32_t		y;
	uint32_t		x_tex;
	uint32_t		y_tex;
	double			win_scale;

	win_scale = (double)ft_game()->view3d->height / (double)HEIGHT * UI_SCALE;
	// win_scale = img->width / (double)tex->width;
	x = 0;
	while (x < tex->width * win_scale)
	{
		y = 0;
		x_tex = x / win_scale;
		while (y < tex->height * win_scale)
		{
			y_tex = y / win_scale;
			put_pixel(img, x, y, ft_get_pixel_color(tex, (t_point){x_tex, y_tex}));
			y++;
		}
		x++;
	}
}

void	draw_ui(void)
{
	draw_ui_minimap();
	draw_ui_health();
	// draw_ui_img(ft_game()->health, ft_game()->textures.ui_health);
	ft_update_hp_bar();
}
