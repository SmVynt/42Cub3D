/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:43:38 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/12 00:04:02 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void draw_vertical_slice(int x, t_rayrender ray)
{
	mlx_image_t		*image;
	double			wall_start;

	image = ft_game()->view3d;
	// wall_start = (((int)(image->height - ray.wall_height * (1 - ft_game()->player->jump_height)) / 2) / PIXEL_SIZE) * PIXEL_SIZE + ft_game()->player->lookupdown;
	wall_start = (((double)image->height - ray.wall_height * (1 - ft_game()->player->jump_height)) / 2) + ft_game()->player->lookupdown;
	// wall_start = wall_start / PIXEL_SIZE * PIXEL_SIZE;
	if (ft_game()->is_bonus)
	{
		draw_ceil_part(ray, x, wall_start);
		draw_floor_part(ray, x, wall_start + ray.wall_height);
	}
	draw_wall_part(ray, x, wall_start);
}

void	draw_wall(mlx_image_t *image, int x)
{
	t_rayrender	ray;
	t_player	*player;

	player = ft_game()->player;
	ray.angle = - FOV_RAD / 2 + x * (FOV_RAD / (double)(image->width - 1));
	ray.dir = ft_mat4_transform_vec2(ft_mat4_rotation_z(ray.angle), player->lookdir);
	ray.bgx = -1;
	ray.start.x = player->pos.x + 0.5f;
	ray.start.y = player->pos.y + 0.5f;
	ray.end = (t_vec2){ray.start.x, ray.start.y};
	ray.wall_dir = DIR_NO;
	ray.end = get_ray_end(&ray, ray.end, ray.dir, 1000, &ray.wall_dir);
	ray.dist = ft_vec2_length((t_vec2){ray.end.x - ray.start.x, ray.end.y - ray.start.y}) * cos(ray.angle);
	if (ray.dist < 1e-9)
		return ;
	ray.wall_height = (double)ft_game()->render.projection_plane_dist / ray.dist;
	ft_game()->render.depth[x / PIXEL_SIZE] = (float)ray.dist;
	draw_vertical_slice(x, ray);
}

t_vec2	get_ray_end(t_rayrender *ray, t_vec2 start, t_vec2 dir, int max_iter, t_direction *wall_dir)
{
	t_vec2	curr;
	t_point	tile;
	int		i;
	int		side;

	curr = start;
	ray->is_doorway = false;
	ray->is_door = false;
	ray->door = NULL;
	start.x -= 0.5;
	start.y -= 0.5;
	if (ft_is_door(start))
		ray->is_doorway = true;
	i = 0;
	while (i < max_iter)
	{
		curr = get_next_wall_intersection(curr, dir, &tile, &side);
		if (tile.u < 0 || tile.v < 0 || tile.u >= ft_game()->map.w || tile.v >= ft_game()->map.h)
		{
			*wall_dir = DIR_NO;
			return (curr);
		}
		ray->is_door = ft_is_door((t_vec2){tile.u, tile.v});
		if (ft_is_wall((t_vec2){tile.u, tile.v}) || ray->is_door)
		{
			ray->wall_type = ft_game()->map.tile[tile.v][tile.u];
			if (ray->is_doorway)
			{
				if (ray->door && !((abs(ray->door->idx.u - tile.u) == 1 && ray->door->idx.v == tile.v)
					|| (ray->door->idx.u == tile.u && abs(ray->door->idx.v - tile.v) == 1)))
					ray->is_doorway = false;
				if (!ray->door && !((abs((int)roundf(start.x) - tile.u) == 1 && roundf(start.y) == tile.v)
					|| (roundf(start.x) == tile.u && abs((int)roundf(start.y) - tile.v) == 1)))
					ray->is_doorway = false;
			}
			if (ray->is_door)
			{
				ray->door = ft_get_door(tile.v, tile.u);
				int new_side;
				t_point tile_check;
				t_vec2 check = get_next_wall_intersection(curr, dir, &tile_check, &new_side);
				if (new_side == side)
				{
					curr = check;
				}
				else if ((side && ((dir.y < 0 && fabsf(check.y - floorf(curr.y)) >= 0.5)
					|| (dir.y > 0 && fabsf(- check.y + floorf(curr.y)) >= 0.5)))
					|| (!side && ((dir.x < 0 && fabsf(check.x - floorf(curr.x)) >= 0.5)
					|| (dir.x > 0 && fabsf(- check.x + floorf(curr.x)) >= 0.5))))
				{
					curr = get_next_wall_intersection(check, dir, &tile_check, &side);
				}
				else
				{
					ray->is_door = false;
					ray->door = NULL;
					side = new_side;
					curr = check;
				}
			}
			if (ray->is_door)
			{
				float coeff = 1.0f;
				if (!side)
					coeff = 0.5f / fabsf(ray->dir.x);
				else
					coeff = 0.5f / fabsf(ray->dir.y);
				curr.x -= coeff * ray->dir.x;
				curr.y -= coeff * ray->dir.y;
				if (ray->door->is_opening)
				{
					ray->is_doorway = true;
					if (side && curr.x - floorf(curr.x) > (DOOR_OPEN_TIME - ray->door->dt)/DOOR_OPEN_TIME)
						continue;
					if (!side && ceilf(curr.y) - curr.y > (DOOR_OPEN_TIME - ray->door->dt)/DOOR_OPEN_TIME)
						continue;
				}
			}
			if (side && dir.y > 0)
				*wall_dir = DIR_SO;
			else if (side)
				*wall_dir = DIR_NO;
			else if (dir.x > 0)
				*wall_dir = DIR_EA;
			else
				*wall_dir = DIR_WE;
			return (curr);
		}
		i++;
	}
	return (t_vec2){0.0, 0.0};
}

