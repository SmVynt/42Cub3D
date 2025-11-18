/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:50:42 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/17 12:17:21 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ft_update_player(void)
{
	t_player	*player;

	player = ft_game()->player;
	ft_update_player_rotation_keys(player);
	ft_update_player_rotation_mouse(player);
	player->lookdir_angle = atan2(player->lookdir.y, player->lookdir.x);
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
			ft_player_try_damage(LAV_DAMAGE_PER_SEC);
	}
	player->mov_control = (t_point){0, 0};
	player->rot_control = (t_point){0, 0};
}
