/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:43:38 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/14 21:31:30 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_vertical_slice(int x, t_rayrender ray)
{
	mlx_image_t	*image;
	t_player	*player;
	double		wall_start;
	double		jump_offset;
	int			y;

	image = ft_game()->view3d;
	player = ft_game()->player;
	jump_offset = ray.wall_height * (1.0 - player->jump_height);
	wall_start = ((double)image->height - jump_offset) / 2.0
		+ player->lookupdown;
	y = PIXEL_SIZE / 2;
	if (ft_game()->is_bonus)
		draw_ceil_part(ray, x, wall_start, &y);
	else
{
		y = wall_start / PIXEL_SIZE * PIXEL_SIZE + PIXEL_SIZE / 2;
		y = ft_clamp(y, 0, image->height);
}
	draw_wall_part(ray, x, wall_start, &y);
	if (ft_game()->is_bonus)
		draw_floor_part(ray, x, wall_start + ray.wall_height, &y);
}

static void	init_ray(t_rayrender *ray, t_player *player, mlx_image_t *image,
				int x)
{
	ray->angle = -FOV_RAD / 2.0 + x * (FOV_RAD / (double)(image->width - 1));
	ray->dir = ft_mat4_transform_vec2(ft_mat4_rotation_z(ray->angle),
			player->lookdir);
	ray->start.x = player->pos.x + 0.5;
	ray->start.y = player->pos.y + 0.5;
	ray->wall_dir = DIR_NO;
}

void	draw_wall(mlx_image_t *image, int x)
{
	t_rayrender	ray;
	t_player	*player;
	t_vec2		diff;

	player = ft_game()->player;
	init_ray(&ray, player, image, x);
	ray.end = get_ray_end(&ray);
	diff.x = ray.end.x - ray.start.x;
	diff.y = ray.end.y - ray.start.y;
	ray.dist = ft_vec2_length(diff) * cos(ray.angle);
	if (ray.dist < 1e-9)
		return ;
	ray.wall_height = (double)ft_game()->render.projection_plane_dist
		/ ray.dist;
	ft_game()->render.depth[x / PIXEL_SIZE] = (double)ray.dist;
	draw_vertical_slice(x, ray);
}
