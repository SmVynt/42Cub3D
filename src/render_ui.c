/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/12 19:52:35 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_update_hp_bar(void)
{
	mlx_image_t	*image;
	int			i;
	int			j;
	t_point		offset;

	image = ft_game()->health_bar;
	if (!image)
		return ;
	memset(image->pixels, 0, image->width * image->height * sizeof(int32_t));
	offset.u = round((double)image->width * (1 - UI_HP_BAR_XSCALE)) / 2;
	offset.v = round((double)image->height * (1 - UI_HP_BAR_YSCALE)) / 2;
	i = offset.u;
	while (i < round((double)((image->width - offset.u) * ft_game()->player->hp)
		/ MAX_HP))
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

void	draw_ui_img(mlx_image_t *img, mlx_texture_t *tex)
{
	uint32_t		x;
	uint32_t		y;
	uint32_t		x_tex;
	uint32_t		y_tex;
	double			win_scale;

	if (!img || !tex)
		return ;
	win_scale = img->width / (double)tex->width;
	x = 0;
	while (x < tex->width * win_scale)
	{
		y = 0;
		x_tex = x / win_scale;
		while (y < tex->height * win_scale)
		{
			y_tex = y / win_scale;
			put_pixel(img, x, y,
				ft_get_pixel_color(tex, (t_point){x_tex, y_tex}));
			y++;
		}
		x++;
	}
}

void	draw_ui_item(mlx_image_t *image, int size, t_point pos,
		mlx_texture_t *tex)
{
	size_t	x;
	size_t	y;
	t_point	screen_pos;
	int		color;

	x = 0;
	while (x < tex->width)
	{
		y = 0;
		while (y < tex->height)
		{
			screen_pos.u = pos.u + (2 * x) + size / 2;
			screen_pos.v = pos.v + (2 * y) + size / 2;
			color = ft_get_pixel_color(tex, (t_point){x, y});
			draw_square(image, 2, screen_pos, color);
			y++;
		}
		x++;
	}
}

void	draw_ui(void)
{
	draw_ui_img(ft_game()->minimap, ft_game()->textures.ui_minimap);
	draw_ui_img(ft_game()->health, ft_game()->textures.ui_health);
	ft_update_hp_bar();
}
