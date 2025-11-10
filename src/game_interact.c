/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_interact.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:25:29 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/10 15:06:37 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	shaky_shaky(void)
{
	t_player	*player;
	t_vec2		perp;
	float		offset;
	double		elapsed;
	float		intensity;

	player = ft_game()->player;
	elapsed = mlx_get_time() - player->shaking_start;
	if (elapsed > SHAKING_TIME)
	{
		player->is_shaking = false;
		player->jump_height = 0.0f;
		return ;
	}
	intensity = expf(-5.0f * elapsed / SHAKING_TIME);
	perp.x = -player->lookdir.y;
	perp.y = player->lookdir.x;
	offset = rand_in_range(-MAX_HOR_SHAKING, MAX_HOR_SHAKING) * intensity;
	player->pos.x += perp.x * offset;
	player->pos.y += perp.y * offset;
	player->jump_height = rand_in_range(-MAX_VERT_SHAKING, MAX_VERT_SHAKING)
		* intensity;
}

void	toggle_switch(t_door *inter_switch)
{
	char	*tile;

	tile = &ft_game()->map.tile[inter_switch->idx.v][inter_switch->idx.u];
	if (*tile == '6')
	{
		*tile = '7';
		ft_game()->player->shaking_start = mlx_get_time();
	}
	else if (*tile == '7')
		*tile = '6';
}

void	swap_chars(char from, char to)
{
	char	**tile;
	int		i;
	int		j;

	tile = ft_game()->map.tile;
	i = 0;
	while (tile[i])
	{
		j = 0;
		while (tile[i][j])
		{
			if (tile[i][j] == from)
				tile[i][j] = to;
			else if (tile[i][j] == to)
				tile[i][j] = from;
			j++;
		}
		i++;
	}
}

static bool	has_key(t_player *player)
{
	t_list		*pocket_items;
	t_item		*item;

	pocket_items = player->pocket;
	if (!pocket_items)
		return (false);
	while (pocket_items)
	{
		item = (t_item *)pocket_items->content;
		if (item->type == IT_KEY)
			return (true);
		pocket_items = pocket_items->next;
	}
	return (false);
}

void	interact(t_gs *game)
{
	t_player	*player;
	t_vec2		vec_door;
	float		door_angle;
	int			i;

	player = game->player;
	i = 0;
	while (i < game->inter_wall_count)
	{
		t_door wall = game->inter_walls[i];
		vec_door = (t_vec2){wall.sprite.pos.x - player->pos.x,
			wall.sprite.pos.y - player->pos.y};
		door_angle = fabsf(ft_angle_between_vec2(vec_door, player->lookdir));
		if (ft_vec2_length(vec_door) <= INTERACT_DIST
			&& door_angle < INTERACT_ANGLE)
		{
			printf("E is pressed\n");
			if (wall.is_switch)
			{	
				printf("switch\n");
				toggle_switch(&wall);
				swap_chars('8', '#');
				player->is_shaking = true;
				player->shaking_start = mlx_get_time();
			}
			else if (!wall.key_needed || has_key(player))
				wall.is_opening = 1;
			else
			{
				printf("door canot open\n");
				// if (wall.key_needed && !has_key(player))
				if (game->msg)
					mlx_delete_image(game->mlx, game->msg);
				game->msg = mlx_put_string(game->mlx, "Door is closed. Key needed!", game->view3d->height - 200, game->view3d->height - 100);
				game->msg_time = mlx_get_time();
			}
		}
		i++;
	}
}


t_vec2	ft_compute_screen_pos(mlx_image_t *image, t_vec2 wall_dir)
{
	t_player		*player;
	t_vec2			screen_pos;
	double			size;
	double			dist;
	double			angle;

	player = ft_game()->player;
	// printf("sprite pos calc %f %f\n",sprite->pos.x, sprite->pos.y);
	// printf("calc dir %f %f\n", sp_dir.x, sp_dir.y);
	dist = ft_vec2_length(wall_dir);
	angle = ft_angle_between_vec2(player->lookdir, wall_dir);
	dist *= cos(angle);
	screen_pos.x = (float)(image->width / 2.0f + (angle / FOV_RAD) * image->width);
	screen_pos.y = (float)(image->height / 2.0f);
	size = (1.0f / dist) * ft_game()->render.projection_plane_dist;
	screen_pos.y += size * 0.5f * ft_game()->player->jump_height + player->lookupdown;
	return (screen_pos);
}

void	print_interact_msg(t_gs *game)
{
	t_player	*player;
	t_vec2		wall_vec;
	float		wall_angle;
	int			i;

	if (game->hints)
		mlx_delete_image(game->mlx, game->hints);
	if (game->msg && mlx_get_time() - game->msg_time > 2)
		mlx_delete_image(game->mlx, game->msg);
	if (false)
	{
	player = game->player;
	i = 0;
	while (i < game->inter_wall_count)
	{
		t_door wall = game->inter_walls[i];
		wall_vec = (t_vec2){wall.sprite.pos.x - player->pos.x,
			wall.sprite.pos.y - player->pos.y};
		wall_angle = fabsf(ft_angle_between_vec2(player->lookdir, wall_vec));
		if (ft_vec2_length(wall_vec) <= INTERACT_DIST
			&& wall_angle < INTERACT_ANGLE)
		{
			if (wall.is_switch || !wall.is_opening)
			{
				char	*msg;
				t_vec2 bckup = wall.sprite.pos;
				// printf("%f %f\n", bckup.x, bckup.y);
				if (wall.is_switch)
				{
					t_vec2 start = player->pos;
					int tile_x, tile_y, side;
					tile_x = start.x;
					tile_y = start.y;
					// printf("%f %f\n", start.x, start.y);
					// wall_vec.x /= ft_vec2_length(wall_vec);
					// wall_vec.y /= ft_vec2_length(wall_vec);
					// printf("dir %f %f\n", wall_vec.x, wall_vec.y);
					start.x += 0.5;
					start.y += 0.5;
					while (!ft_is_wall((t_vec2){tile_x, tile_y}))
						start = get_next_wall_intersection(start, wall_vec, &tile_x, &tile_y, &side);
					// if (!ft_is_special_wall((t_vec2){tile_x, tile_y}))
					// {
					// 	i++;
					// 	continue ;
					// }
					if (!side)
						wall.sprite.pos.x -= ft_signf(wall_vec.x) * 0.5f;
					else
						wall.sprite.pos.y -= ft_signf(wall_vec.y) * 0.5f;
					msg = "[E] to interact";
				}
				else
					msg = "[E] to open";
				// printf("sprite pos %f %f\n", wall.sprite.pos.x, wall.sprite.pos.y);
				t_vec2 screen_pos = ft_compute_screen_pos(game->view3d, wall_vec);
				// printf("sprite pos %f %f\n", wall.sprite.pos.x, wall.sprite.pos.y);
				game->hints = mlx_put_string(game->mlx, msg, screen_pos.x, screen_pos.y);
				wall.sprite.pos = bckup;
				break ;
			}
		}
		i++;
	}
}
}
