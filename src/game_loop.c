/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:50:42 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/03 23:27:36 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_is_special_wall(t_vec2 p, const char *wall_type)
{
	t_gs	*game;
	t_map	*map;
	int		x;
	int		y;

	game = ft_game();
	map = &game->map;
	x = (int)roundf(p.x);
	y = (int)roundf(p.y);
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (false);
	if (ft_strchar(wall_type, map->tile[y][x]) != NULL)
		return (true);
	return (false);
}

bool ft_is_wall(t_vec2 p)
{
	t_gs	*game;
	t_map	*map;
	int		x;
	int		y;

	game = ft_game();
	map = &game->map;
	x = (int)roundf(p.x);
	y = (int)roundf(p.y);
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (false);
	if (ft_strchar(MAP_WALL_CHARS, map->tile[y][x]) != NULL)
		return (true);
	if (ft_strchar(MAP_DOOR_CHARS, map->tile[y][x]) != NULL && ft_get_door(y,x)->closed)
		return (true);
	return (false);
}

bool ft_is_door(t_vec2 p)
{
	t_gs	*game;
	t_map	*map;
	int		x;
	int		y;

	game = ft_game();
	map = &game->map;
	x = (int)roundf(p.x);
	y = (int)roundf(p.y);
	if (x < 0 || y < 0 || x >= map->w || y >= map->h)
		return (false);
	if (ft_strchar(MAP_DOOR_CHARS, map->tile[y][x]) != NULL) //&& ft_get_door(y,x)->closed)
		return (true);
	return (false);
}

static void	ft_clamp_new_position(t_vec2 *player_pos,t_vec2 new_pos_delta)
{
	t_vec2	border_offset;
	t_vec2	closest_tile_border;

	if (new_pos_delta.x < 0.0f)
		closest_tile_border.x = (float)((int)(player_pos->x)) + 0.5f + TILE_BORDER;
	else
		closest_tile_border.x = (float)((int)(player_pos->x + 1.0f)) - 0.5f - TILE_BORDER;
	if (new_pos_delta.x == 0.0f)
		closest_tile_border.x = player_pos->x;
	if (new_pos_delta.y < 0.0f)
		closest_tile_border.y = (float)((int)(player_pos->y)) + 0.5f + TILE_BORDER;
	else
		closest_tile_border.y = (float)((int)(player_pos->y + 1.0f)) - 0.5f - TILE_BORDER;
	if (new_pos_delta.y == 0.0f)
		closest_tile_border.y = player_pos->y;
	border_offset = (t_vec2){ft_signf(new_pos_delta.x) * TILE_BORDER, ft_signf(new_pos_delta.y) * TILE_BORDER};
	if (ft_is_wall((t_vec2){player_pos->x + new_pos_delta.x + border_offset.x, player_pos->y}))
		new_pos_delta.x = closest_tile_border.x - player_pos->x;
	if (ft_is_wall((t_vec2){player_pos->x, player_pos->y + new_pos_delta.y + border_offset.y}))
		new_pos_delta.y = closest_tile_border.y - player_pos->y;
	player_pos->x += new_pos_delta.x;
	player_pos->y += new_pos_delta.y;
}

void	ft_update_player(void)
{
	t_player	*player;
	t_vec2		move_step;
	t_vec2		new_pos;
	float		maxlookupdown;

	player = ft_game()->player;
	maxlookupdown = ft_game()->view3d->height / 2;
	if (player->rot_control.u != 0)
	{
		player->lookdir = ft_mat4_transform_vec2(ft_mat4_rotation_z(player->rot_control.u * ROTATIONSPEED * ft_game()->dt), player->lookdir);
	}
	if (player->rot_control.v != 0)
	{
		player->lookupdown += player->rot_control.v * ROTATIONSPEED * 500 * ft_game()->dt;
		if (player->lookupdown > maxlookupdown)
			player->lookupdown = maxlookupdown;
		if (player->lookupdown < -maxlookupdown)
			player->lookupdown = -maxlookupdown;
		player->rot_control.v = 0.0f;
	}
	if (player->mouse_diff.x != 0.0f)
	{
		player->lookdir = ft_mat4_transform_vec2(ft_mat4_rotation_z(-player->mouse_diff.x * ROTATIONSPEED * MOUSE_XSENS * ft_game()->dt), player->lookdir);
		player->mouse_diff.x = 0.0f;
	}
	if (player->mouse_diff.y != 0.0f)
	{
		player->lookupdown += player->mouse_diff.y * ROTATIONSPEED * MOUSE_YSENS * ft_game()->dt;
		maxlookupdown = ft_game()->view3d->height / 2;
		if (player->lookupdown > maxlookupdown)
			player->lookupdown = maxlookupdown;
		if (player->lookupdown < -maxlookupdown)
			player->lookupdown = -maxlookupdown;
		player->mouse_diff.y = 0.0f;
	}
	if (player->mov_control.v != 0 || player->mov_control.u != 0)
	{
		move_step = ft_normalize_vec2((t_vec2){player->mov_control.u, player->mov_control.v});
		// move_step = (t_vec2){player->mov_control.u, player->mov_control.v};
		move_step.x *= PLAYERSPEED * ft_game()->dt;
		move_step.y *= PLAYERSPEED * ft_game()->dt;
		// printf("move_step: %.2f, %.2f\n", move_step.x, move_step.y);
		new_pos.x = player->lookdir.x * move_step.y;
		new_pos.y = player->lookdir.y * move_step.y;
		new_pos.x -= player->lookdir.y * move_step.x;
		new_pos.y += player->lookdir.x * move_step.x;
		ft_clamp_new_position(&player->pos, new_pos);
	}
	if (player->is_jumping)
	{
		player->jump_impuls += -9.8f * ft_game()->dt;
		player->jump_height += player->jump_impuls * ft_game()->dt;
		if (player->jump_height < 0.1f)
		{
			player->jump_height = 0.1f;
			player->is_jumping = false;
		}
	}
	player->mov_control = (t_point){0, 0};
	player->rot_control = (t_point){0, 0};
}

static void	ft_update_view3d(void *param)
{
	mlx_image_t	*image;

	if (!param)
		return ;
	image = (mlx_image_t *)param;
	memset(image->pixels, 0, image->width * image->height * sizeof(int32_t));
	draw_walls(ft_game()->view3d);
	// draw_doors(ft_game()->view3d);
	draw_sprites(ft_game()->view3d);
}

void	ft_update_graphics(void)
{
	ft_update_view3d(ft_game()->view3d);
	ft_update_hud(ft_game()->hud);
	ft_update_minimap(ft_game()->miniplayer);
}

void	ft_update_hud(void *param)
{
	mlx_image_t	*image;
	t_list		*pocket_items;
	t_item		*item;

	pocket_items = ft_game()->player->pocket;
	if (!param || !pocket_items)
		return ;
	image = (mlx_image_t *)param;
	// memset(image->pixels, COLOR_RED_TRANSP, image->width * image->height * sizeof(int32_t));
	int i = 0;
	while (pocket_items)
	{
		item = (t_item *)pocket_items->content;
		draw_item(image, 64, (t_point){0, i * 64}, item->sprite.texture);
		pocket_items = pocket_items->next;
		i++;
	}
}

void	ft_update_minimap(void *param)
{
	mlx_image_t	*image;

	if (!param)
		return ;
	image = (mlx_image_t *)param;
	memset(image->pixels, 0, image->width * image->height * sizeof(int32_t));
	//draw_player(image);
	draw_map(image, &ft_game()->map);
}

static void ft_update_dt(void)
{
	static struct timeval last_time;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec == 0) {
		last_time = current_time;
	}

	float elapsed = (current_time.tv_sec - last_time.tv_sec) +
					(current_time.tv_usec - last_time.tv_usec) / 1000000.0f;
	if (elapsed > MAX_DT)
		elapsed = MAX_DT;
	ft_game()->dt = elapsed;
	last_time = current_time;
}

void	ft_update(void *param)
{
	t_gs		*game;
	t_player	*player;
	int			i;
	// bool		upd_doors;

	game = ft_game();
	player = game->player;
	(void)param;
	ft_update_dt();
	i = 0;
	if (player->is_shaking)
		shaky_shaky();
	// upd_doors = false;
	while(i < game->inter_wall_count)
	{
		if (ft_game()->inter_walls[i].is_opening)
		{
			open_door(i);
			// upd_doors = true;
		}
		i++;
	}
	ft_update_chars();
	if (player->mov_control.u != 0
		|| player->mov_control.v != 0
		|| player->rot_control.u != 0
		|| player->rot_control.v != 0
		|| player->mouse_diff.x != 0.0f
		|| player->mouse_diff.y != 0.0f
		|| player->is_jumping)
		// || upd_doors)
	{
		ft_update_player();
	}
	ft_update_graphics();
}
