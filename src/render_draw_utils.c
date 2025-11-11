/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/11 15:04:00 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	allocate_depth_buffer(t_gs *game, int32_t width)
{
	if (game->render.depth)
		free(game->render.depth);
	game->render.depth = malloc(sizeof(float) * (width / PIXEL_SIZE + 2));
	if (!game->render.depth)
		return (false);
	game->render.projection_plane_dist = (width / 2.0) / tan(FOV_RAD / 2.0);
	return (true);
}

void	setup_minimap_positions(t_gs *game, int32_t width, int32_t height)
{
	game->mmap.miniplayer_pos_show = (t_point){
		(width / 16) + round((float)height * 0.11f),
		(height / 2) + round((float)height * 0.025f)};
	game->mmap.miniplayer_pos_hide = (t_point){
		game->mmap.miniplayer_pos_show.u + width / 16,
		game->mmap.miniplayer_pos_show.v + height / 2};
	game->mmap.minimap_pos_show = (t_point){width / 16, height / 2};
	game->mmap.minimap_pos_hide = (t_point){
		game->mmap.minimap_pos_show.u + width / 16,
		game->mmap.minimap_pos_show.v + height / 2};
}

void	ft_fill_split_bg(mlx_image_t *bg)
{
	uint32_t	u;
	uint32_t	v;
	uint32_t	center;

	center = bg->height / (2 * PIXEL_SIZE) * PIXEL_SIZE;
	v = 0;
	while (v < center)
	{
		u = -1;
		while (++u < bg->width)
			put_pixel(bg, u, v, ft_game()->render.top_color);
		v++;
	}
	while (v < bg->height)
	{
		u = -1;
		while (++u < bg->width)
			put_pixel(bg, u, v, ft_game()->render.bottom_color);
		v++;
	}
}

void	fill_background(mlx_image_t *image, uint32_t color)
{
	uint32_t	*pixels;
	int			total;
	int			i;

	pixels = (uint32_t *)image->pixels;
	total = image->width * image->height;
	i = 0;
	while (i < total)
	{
		pixels[i] = color;
		i++;
	}
}

void	draw_walls(mlx_image_t *image)
{
	uint32_t	x;

	x = PIXEL_SIZE / 2;
	while (x < ft_game()->view3d->width)
	{
		draw_wall(image, x);
		x += PIXEL_SIZE;
	}
	draw_wall(image, x);
}
