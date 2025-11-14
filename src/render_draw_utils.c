/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:05 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/14 20:50:32 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	allocate_depth_buffer(t_gs *game, int32_t width)
{
	if (game->render.depth)
		free(game->render.depth);
	game->render.depth = malloc(sizeof(double) * (width / PIXEL_SIZE + 2));
	if (!game->render.depth)
		return (false);
	game->render.projection_plane_dist = (width / 2.0) / tan(FOV_RAD / 2.0);
	return (true);
}

void	setup_minimap_positions(t_gs *game, int32_t width, int32_t height)
{
	t_point			mmap_pos;
	mlx_texture_t	*tex;
	mlx_image_t		*image;

	mmap_pos.u = round(width / 16.0);
	mmap_pos.v = round(height / 2.0);
	tex = game->textures.ui_minimap;
	image = game->minimap;
	game->mmap.miniplayer_pos_show = (t_point){
		mmap_pos.u + round((double)image->width
			* (MM_XSTART / (double)tex->width)),
		mmap_pos.v + round((double)image->height
			* (MM_YSTART / (double)tex->height))};
	game->mmap.miniplayer_pos_hide = (t_point){
		game->mmap.miniplayer_pos_show.u + mmap_pos.u,
		game->mmap.miniplayer_pos_show.v + mmap_pos.v};
	game->mmap.minimap_pos_show = mmap_pos;
	game->mmap.minimap_pos_hide = (t_point){
		game->mmap.minimap_pos_show.u + mmap_pos.u,
		game->mmap.minimap_pos_show.v + mmap_pos.v};
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

void	draw_walls(mlx_image_t *image)
{
	uint32_t	x;
	t_player	*player;

	player = ft_game()->player;
	if (player->lookdir_angle < 0)
		player->lookdir_angle += 2.0 * M_PI;
	ft_game()->render.bg_start_offset = player->lookdir_angle
	* (double)ft_game()->textures.bg->width / (2.0 * M_PI);
	x = 0;
	while (x < ft_game()->view3d->width)
	{
		draw_wall(image, x + PIXEL_SIZE / 2);
		x += PIXEL_SIZE;
	}
}
