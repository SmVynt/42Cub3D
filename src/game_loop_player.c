/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:50:42 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/14 11:27:02 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_clamp_new_position(t_vec2 *player_pos, t_vec2 new_pos_delta)
{
	t_vec2	border_offset;
	t_vec2	closest_tile_border;
	t_vec2	signs;

	signs.x = ft_signd(new_pos_delta.x);
	signs.y = ft_signd(new_pos_delta.y);
	closest_tile_border.x = round(player_pos->x + signs.x * 0.5)
		- signs.x * (TILE_BORDER + 0.5);
	if (new_pos_delta.x == 0.0)
		closest_tile_border.x = player_pos->x;
	closest_tile_border.y = round(player_pos->y + signs.y * 0.5)
		- signs.y * (TILE_BORDER + 0.5);
	if (new_pos_delta.y == 0.0)
		closest_tile_border.y = player_pos->y;
	border_offset = (t_vec2){ft_signd(new_pos_delta.x) * TILE_BORDER,
		ft_signd(new_pos_delta.y) * TILE_BORDER};
	if (ft_is_wall((t_vec2){player_pos->x + new_pos_delta.x
			+ border_offset.x, player_pos->y}))
		new_pos_delta.x = closest_tile_border.x - player_pos->x;
	if (ft_is_wall((t_vec2){player_pos->x, player_pos->y
			+ new_pos_delta.y + border_offset.y}))
		new_pos_delta.y = closest_tile_border.y - player_pos->y;
	player_pos->x += new_pos_delta.x;
	player_pos->y += new_pos_delta.y;
}

static void	ft_update_player_rotation_keys(t_player *player)
{
	double	maxlookupdown;

	maxlookupdown = ft_game()->view3d->height / 2;
	if (player->rot_control.u != 0)
	{
		player->lookdir = ft_mat4_transform_vec2(
				ft_mat4_rotation_z(player->rot_control.u
					* ROTATIONSPEED * ft_game()->dt),
				player->lookdir);
	}
	if (player->rot_control.v != 0 && ft_game()->is_bonus)
	{
		player->lookupdown += player->rot_control.v
			* ROTATIONSPEED * 500 * ft_game()->dt;
		player->lookupdown = ft_clamp(player->lookupdown,
				-maxlookupdown, maxlookupdown);
		player->rot_control.v = 0.0;
	}
}

static void	ft_update_player_rotation_mouse(t_player *player)
{
	double	maxlookupdown;

	maxlookupdown = ft_game()->view3d->height / 2;
	if (player->mouse_diff.x != 0.0)
	{
		player->lookdir = ft_mat4_transform_vec2(
				ft_mat4_rotation_z(-player->mouse_diff.x
					* ROTATIONSPEED * MOUSE_XSENS * ft_game()->dt),
				player->lookdir);
		player->mouse_diff.x = 0.0;
	}
	if (player->mouse_diff.y != 0.0 && ft_game()->is_bonus)
	{
		player->lookupdown += player->mouse_diff.y
			* ROTATIONSPEED * MOUSE_YSENS * ft_game()->dt;
		maxlookupdown = ft_game()->view3d->height / 2;
		if (player->lookupdown > maxlookupdown)
			player->lookupdown = maxlookupdown;
		if (player->lookupdown < -maxlookupdown)
			player->lookupdown = -maxlookupdown;
		player->mouse_diff.y = 0.0;
	}
}

static void	ft_update_player_movement(t_player *player)
{
	t_vec2		move_step;
	t_vec2		new_pos;

	if (player->mov_control.v != 0 || player->mov_control.u != 0)
	{
		move_step = ft_normalize_vec2(
				(t_vec2){player->mov_control.u, player->mov_control.v});
		move_step.x *= PLAYERSPEED * ft_game()->dt;
		move_step.y *= PLAYERSPEED * ft_game()->dt;
		new_pos.x = player->lookdir.x * move_step.y;
		new_pos.y = player->lookdir.y * move_step.y;
		new_pos.x -= player->lookdir.y * move_step.x;
		new_pos.y += player->lookdir.x * move_step.x;
		ft_clamp_new_position(&player->pos, new_pos);
	}
}

void	ft_update_player(void)
{
	t_player	*player;

	player = ft_game()->player;
	ft_update_player_rotation_keys(player);
	ft_update_player_rotation_mouse(player);
	if (ft_game()->game_over == 0)
	{
		ft_update_player_movement(player);
		if (player->is_jumping)
		{
			player->jump_impuls += -9.8f * ft_game()->dt;
			player->jump_height += player->jump_impuls * ft_game()->dt;
			if (player->jump_height < 0.1)
			{
				player->jump_height = 0.1;
				player->is_jumping = false;
			}
		}
		else if (ft_is_lava(player->pos))
			ft_player_try_damage(LAV_DAMAGE_PER_SEC * ft_game()->dt);
	}
	player->mov_control = (t_point){0, 0};
	player->rot_control = (t_point){0, 0};
}
