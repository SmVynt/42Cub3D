/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:43:38 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/27 01:44:23 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void draw_vertical_slice(int x, t_rayrender ray);

static void ft_draw_cubemap(mlx_image_t *image, t_rayrender *ray, t_point screen_coords)
{
	mlx_texture_t	*bg;
	t_point			pixel;
	float			angle;
	float			scale_correction;
	float			new_y;

	bg = ft_game()->textures.bg;
	if (ray->bgx == -1)
	{
		angle = atan2(ray->dir.y, ray->dir.x);
		if (angle < 0)
			angle += 2.0 * M_PI;
		ray->bgx = (int)((angle / (2.0 * M_PI)) * (float)bg->width);
	}
	pixel.u = ray->bgx;
	scale_correction = 0.5f * (float)bg->height / (float)image->height;
	new_y = ((float)screen_coords.v - (float)image->height / 2) * scale_correction + (float)bg->height / 2;
	pixel.v = (int)new_y - (int)(ft_game()->player->lookupdown * scale_correction);
	draw_square(image, PIXEL_SIZE, screen_coords, ft_get_pixel_color(bg, pixel));
}

static double get_dist_to_screen_point(int y, t_rayrender ray)
{
	double screen_center_y;
	double height_from_center;
	double jump_scale_factor;
	double dist;

	screen_center_y = ft_game()->view3d->height / 2.0;
	height_from_center = y - screen_center_y - ft_game()->player->lookupdown;
	jump_scale_factor = ft_game()->player->jump_height + ft_signf(height_from_center) * 1.0;
	dist = (ft_game()->render.projection_plane_dist * jump_scale_factor)
	                 / (2.0 * fabs(height_from_center) * cos(ray.angle));
	return (dist);
}


float	ft_height_delta(float distance)
{
	float jump_height;

	jump_height = (float)ft_game()->player->jump_height;
	if (distance < 0.0001f)
		distance = 0.0001f;
	return (ft_game()->render.projection_plane_dist / distance) * (jump_height + 1.0f);
}

static void	get_next_point_to_draw(t_point *p, int *slope_err,
		t_point diff, t_point dir);

static t_vec2 get_ray_end(t_rayrender *ray, t_vec2 start, t_vec3 dir, int max_steps, t_direction *wall_dir);

bool hit_wall(t_point p, t_map map, mlx_image_t* image)
{
	int x;
	int y;

	if (p.u < 0 || (unsigned int)p.u >= image->width || p.v < 0 || (unsigned int)p.v >= image->height)
		return (true);
	x = (p.u - MAP_SCALE / 2) / MAP_SCALE;
	y = (p.v - MAP_SCALE / 2) / MAP_SCALE;
	if (x < 0 || x >= map.w || y < 0 || y >= map.h)
		return (true);
	if (ft_strchar(MAP_WALL_CHARS, map.tile[y][x]) != NULL)
		return (true);
	return (false);
}

void	draw_line_ray(mlx_image_t *image, t_point p0, t_vec3 lookdir, t_map map, int x)
{
	t_point		diff;
	t_point		dir;
	int			slope_err;
	t_point		draw_point;

	(void) x;
	draw_point = (t_point){p0.u, p0.v};
	diff.u = fabsf(lookdir.x * 1000000);
	diff.v = fabsf(lookdir.y * 1000000);
	dir.u = (lookdir.x > 0.0) - (lookdir.x < 0.0);
	dir.v = (lookdir.y > 0.0) - (lookdir.y < 0.0);
	slope_err = diff.u - diff.v;
	int max_iter = 1000;
	int i = 0;
	while (i < max_iter)
	{
		if (hit_wall(draw_point, map, image))
			break ;
		put_pixel(image, draw_point.u, draw_point.v, COLOR_RED);
		get_next_point_to_draw(&draw_point, &slope_err, diff, dir);
		i++;
	}
}

static int	ft_find_texture_u(mlx_texture_t **texture, t_rayrender ray)
{
	int	tex_u;
	t_vec2 loc;
	t_direction dir;

	dir = ray.wall_dir;
	loc = ray.end;
	if (ray.is_door)
	{
		*texture = ray.door->sprite.texture;
		if (ray.door->is_opening)
		{
			loc.x -= (DOOR_OPEN_TIME - ray.door->dt)/DOOR_OPEN_TIME;
			loc.y += (DOOR_OPEN_TIME - ray.door->dt)/DOOR_OPEN_TIME;
		}
	}
	if (dir == DIR_SO)
	{
		if (!ray.is_door)
			*texture = ft_game()->textures.wall.tex[DIR_SO];
		tex_u = (int)((loc.x - floorf(loc.x)) * ((*texture)->width));
	}
	else if (dir == DIR_NO)
	{
		if (!ray.is_door)
			*texture = ft_game()->textures.wall.tex[DIR_NO];
		tex_u = (int)((1.0f -(loc.x - floorf(loc.x))) * ((*texture)->width));
	}
	else if (dir == DIR_EA)
	{
		if (!ray.is_door)
			*texture = ft_game()->textures.wall.tex[DIR_EA];
		tex_u = (int)((loc.y - floorf(loc.y)) * ((*texture)->width));
	}
	else
	{
		if (!ray.is_door)
			*texture = ft_game()->textures.wall.tex[DIR_WE];
		tex_u = (int)((1.0f - (loc.y - floorf(loc.y))) * ((*texture)->width));
	}
	return (tex_u);
}

void ft_draw_wall_part(t_rayrender ray, int x, int wall_start)
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	t_point			pixel;
	int				delta;
	uint32_t		color;

	image = ft_game()->view3d;
	pixel.u = ft_find_texture_u(&texture, ray);
	delta = 0;
	wall_start = wall_start / PIXEL_SIZE * PIXEL_SIZE + PIXEL_SIZE / 2;
	while (delta <= ray.wall_height)
	{
		if ((wall_start + delta) >= (int)image->height)
			break ;
		pixel.v = (int)(delta / ray.wall_height * texture->height);
		// if (ray.is_door)
		// 	color = 0xFF00001A;
		// else
			color = ft_get_pixel_color(texture, pixel);
		if (color != 0)
			draw_square(image, PIXEL_SIZE, (t_point){x, wall_start + delta}, color);
		else
			ft_draw_cubemap(image, &ray, (t_point){x, wall_start + delta});
		delta += PIXEL_SIZE;
	}
}

static void ft_draw_floor_part(t_rayrender ray, int x, int wall_end)
{
	mlx_image_t *image;
	t_point		pixel;
	int			y;
	double		dist;
	uint32_t	color;

	image = ft_game()->view3d;
	y = wall_end / PIXEL_SIZE * PIXEL_SIZE + PIXEL_SIZE / 2;
	while (y < (int)image->height)
	{
		dist = get_dist_to_screen_point(y, ray);
		pixel.u = ft_get_tex_coord(ray.start.x + ray.dir.x * dist, ft_game()->textures.wall.tex[DIR_WE]->width);
		pixel.v = ft_get_tex_coord(ray.start.y + ray.dir.y * dist, ft_game()->textures.wall.tex[DIR_NO]->height);
		// draw_square(image, PIXEL_SIZE, (t_point){x, y}, ft_get_pixel_color(ft_game()->textures.no, pixel));
		color = ft_get_pixel_color(ft_game()->textures.wall.tex[DIR_WE], pixel);
		if (color != 0)
			draw_square(image, PIXEL_SIZE, (t_point){x, y}, color);
		else
			ft_draw_cubemap(image, &ray, (t_point){x, y});
		y += PIXEL_SIZE;
	}
}

static void ft_draw_ceil_part(t_rayrender ray, int x, int wall_start)
{
	mlx_image_t *image;
	t_point		pixel;
	int			y;
	double		dist;
	uint32_t	color;

	image = ft_game()->view3d;
	y = PIXEL_SIZE / 2;
	while (y < wall_start)
	{
		dist = get_dist_to_screen_point(y, ray);
		pixel.u = ft_get_tex_coord(ray.start.x - ray.dir.x * dist, ft_game()->textures.wall.tex[DIR_NO]->width);
		pixel.v = ft_get_tex_coord(ray.start.y - ray.dir.y * dist, ft_game()->textures.wall.tex[DIR_NO]->height);
		// draw_square(image, PIXEL_SIZE, (t_point){x, y}, ft_get_pixel_color(ft_game()->textures.ea, pixel));
		// y += PIXEL_SIZE;
		color = ft_get_pixel_color(ft_game()->textures.wall.tex[DIR_NO], pixel);
		if (color != 0)
			draw_square(image, PIXEL_SIZE, (t_point){x, y}, color);
		else
			ft_draw_cubemap(image, &ray, (t_point){x, y});
		y += PIXEL_SIZE;
	}
}

void	draw_wall(mlx_image_t *image, int x)
{
	t_rayrender	ray;
	t_player	*player;

	player = ft_game()->player;
	ray.angle = - FOV_RAD / 2 + x * (FOV_RAD / (double)(image->width - 1));
	ray.dir = ft_mat4_transform_vec3(ft_mat4_rotation_z(ray.angle), player->lookdir);
	ray.bgx = -1;
	ray.start.x = player->pos.x + 0.5f;
	ray.start.y = player->pos.y + 0.5f;
	ray.end = (t_vec2){ray.start.x, ray.start.y};
	// ray.wall_dir = COLOR_GREEN;
	ray.wall_dir = DIR_NO;
	ray.end = get_ray_end(&ray, ray.end, ray.dir, 1000, &ray.wall_dir);
	ray.dist = ft_vec2_length((t_vec2){ray.end.x - ray.start.x, ray.end.y - ray.start.y}) * cos(ray.angle);
	if (ray.dist < 1e-9)
		return ;
	ray.wall_height = ft_game()->render.projection_plane_dist / ray.dist;
	ft_game()->render.depth[x / PIXEL_SIZE] = (float)ray.dist;
	draw_vertical_slice(x, ray);
}

static void draw_vertical_slice(int x, t_rayrender ray)
{
	mlx_image_t		*image;
	int	wall_start;

	image = ft_game()->view3d;
	wall_start = (((int)(image->height - ray.wall_height * (1 - ft_game()->player->jump_height)) / 2) / PIXEL_SIZE) * PIXEL_SIZE + ft_game()->player->lookupdown;

	if (true)
		ft_draw_ceil_part(ray, x, wall_start);
	if (true)
		ft_draw_wall_part(ray, x, wall_start);
	if (true)
		ft_draw_floor_part(ray, x, wall_start + ray.wall_height);
}


static void	get_next_point_to_draw(t_point *p, int *slope_err,
		t_point diff, t_point dir)
{
	int	err2;

	err2 = 2 * (*slope_err);
	if (err2 >= -diff.v)
	{
		*slope_err -= diff.v;
		p->u += dir.u;
	}
	if (err2 <= diff.u)
	{
		*slope_err += diff.u;
		p->v += dir.v;
	}
}

static t_vec2 get_next_wall_intersection(t_vec2 pos, t_vec3 dir, int *tile_x, int *tile_y, int *side)
{
	t_vec2	hit_point;
	t_vec2	next_wall;
	t_vec2	dist;

	int step_x = (dir.x >= 0) - (dir.x <= 0);
	int step_y = (dir.y >= 0) - (dir.y <= 0);
	if (dir.x > 0)
		next_wall.x = ceil(pos.x);
	else
		next_wall.x = floor(pos.x);
	if (fabs(next_wall.x - pos.x) < 1e-9)
		next_wall.x += step_x;
	if (dir.y > 0)
		next_wall.y = ceil(pos.y);
	else
		next_wall.y = floor(pos.y);
	if (fabs(next_wall.y - pos.y) < 1e-9)
		next_wall.y += step_y;
	if (fabs(dir.x) > 1e-9)
		dist.x = (next_wall.x - pos.x) / dir.x;
	else
		dist.x = INFINITY;
	if (fabs(dir.y) > 1e-9)
		dist.y = (next_wall.y - pos.y) / dir.y;
	else
		dist.y = INFINITY;
	if (dist.x < dist.y)
	{
		hit_point.x = next_wall.x;
		hit_point.y = pos.y + dist.x * dir.y;
		*tile_x = (int)next_wall.x;
		if (step_x < 0)
			*tile_x -= 1;
		*tile_y = (int)floor(hit_point.y);
		*side = 0;
	}
	else
	{
		hit_point.x = pos.x + dist.y * dir.x;
		hit_point.y = next_wall.y;
		*tile_x = (int)floor(hit_point.x);
		*tile_y = (int)next_wall.y;
		if (step_y < 0)
			*tile_y -= 1;
		*side = 1;
	}
	return hit_point;
}

static t_vec2 get_ray_end(t_rayrender *ray, t_vec2 start, t_vec3 dir, int max_iter, t_direction *wall_dir)
{
	t_vec2	curr;
	t_point	tile;
	int		i;
	int		side;

	curr = start;
	i = 0;
	while (i < max_iter)
	{
		curr = get_next_wall_intersection(curr, dir, &tile.u, &tile.v, &side);
		// printf("Hit wall at (%.2f, %.2f), tile[%d][%d], side=%d\n",
		//        hit_point.x, hit_point.y, tile_y, tile_x, side);
		ray->is_door = ft_is_door((t_vec2){tile.u, tile.v});
		ray->wall_type = ft_game()->map.tile[tile.v][tile.u];
		if (ft_is_wall((t_vec2){tile.u, tile.v}) || ray->is_door)
		{
			if (ray->is_door)
			{
				ray->door = ft_get_door(tile.v, tile.u);
				int new_side;
				t_point tile_check;
				t_vec2 check = get_next_wall_intersection(curr, dir, &tile_check.u, &tile_check.v, &new_side);
				if (new_side == side)
				{
					curr = check;
				}
				else if ((side && ((dir.y < 0 && fabsf(check.y - floorf(curr.y)) >= 0.5)
					|| (dir.y > 0 && fabsf(- check.y + floorf(curr.y)) >= 0.5)))
					|| (!side && ((dir.x < 0 && fabsf(check.x - floorf(curr.x)) >= 0.5)
					|| (dir.x > 0 && fabsf(- check.x + floorf(curr.x)) >= 0.5))))
				{
					curr = get_next_wall_intersection(check, dir, &tile_check.u, &tile_check.v, &side);
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
					// printf("%f\n",ft_get_door(tile.v, tile.u)->dt/DOOR_OPEN_TIME);
					if (side && curr.x - floorf(curr.x) > (DOOR_OPEN_TIME - ray->door->dt)/DOOR_OPEN_TIME)
						continue;
					if (!side && ceilf(curr.y) - curr.y > (DOOR_OPEN_TIME - ray->door->dt)/DOOR_OPEN_TIME)
						continue;
				}
			}
			// if (side && dir.y > 0)
			// 	*color = COLOR_RED;
			// else if (side)
			// 	*color = COLOR_GREEN;
			// else if (dir.x > 0)
			// 	*color = COLOR_YELLOW;
			// else
			// 	*color = COLOR_BLUE;
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
	}
	return (t_vec2){0.0, 0.0};
}

void	draw_sprite(mlx_image_t *image, t_sprite *sprite)
{
	t_spriterender	*sp;
	int				x;
	int				y;

	if (!sprite->texture || !sprite->texture->pixels)
		return ;
	sp = &sprite->sp;
	if (!sp->visible)
		return ;
	x = (PIXEL_SIZE - sp->start.u % PIXEL_SIZE) % PIXEL_SIZE + PIXEL_SIZE / 2;
	while (x < sp->size.u)
	{
		sp->screen.u = sp->start.u + x;
		if (sp->screen.u >= 0 && sp->screen.u < (int)image->width)
		{
			if (sp->dist > ft_game()->render.depth[sp->screen.u / PIXEL_SIZE])
			{
				x += PIXEL_SIZE;
				continue ;
			}
			y = (PIXEL_SIZE - sp->start.v % PIXEL_SIZE) % PIXEL_SIZE + PIXEL_SIZE / 2;
			while (y < sp->size.v)
			{
				sp->screen.v = sp->start.v + y;
				if (sp->screen.v >= 0 && sp->screen.v < (int)image->height)
				{
					draw_square(image, PIXEL_SIZE, (t_point){sp->screen.u, sp->screen.v},
						ft_get_pixel_color(sprite->texture, (t_point){
							(int)((float)x / (float)sp->size.u * (float)sprite->texture->width),
							(int)((float)y / (float)sp->size.v * (float)sprite->texture->height)}));
				}
				y += PIXEL_SIZE;
			}
		}
		x += PIXEL_SIZE;
	}
}
