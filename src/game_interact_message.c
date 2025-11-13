/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_interact_message.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:25:29 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/12 19:53:33 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	print_message_sub(t_gs *game, int i)
{
	char	*msg;
	double	bck;

	if (game->inter_walls[i].is_switch || !game->inter_walls[i].is_opening)
	{
		bck = game->inter_walls[i].sprite.pos.x;
		if (game->inter_walls[i].is_switch)
			msg = "[E] to interact";
		else
			msg = "[E] to open";
		ft_calculate_sprite(game->view3d, &game->inter_walls[i].sprite);
		game->inter_walls[i].sprite.pos.x = bck;
		game->hints = mlx_put_string(game->mlx, msg,
				game->inter_walls[i].sprite.sp.screen_pos.x,
				game->inter_walls[i].sprite.sp.screen_pos.y
				+ game->player->lookupdown + 0.5 * game->player->jump_height
				* game->inter_walls[i].sprite.sp.max_size);
		return (true);
	}
	return (false);
}

void	print_interact_msg(t_gs *game)
{
	t_player	*player;
	t_vec2		vec_door;
	double		door_angle;
	int			i;

	if (game->hints)
		mlx_delete_image(game->mlx, game->hints);
	if (game->msg && mlx_get_time() - game->msg_time > 2)
		mlx_delete_image(game->mlx, game->msg);
	player = game->player;
	i = 0;
	while (i < game->inter_wall_count)
	{
		vec_door = (t_vec2){game->inter_walls[i].sprite.pos.x - player->pos.x,
			game->inter_walls[i].sprite.pos.y - player->pos.y};
		door_angle = fabs(ft_angle_between_vec2(vec_door,
					(t_vec2){player->lookdir.x, player->lookdir.y}));
		if (ft_vec2_length(vec_door) <= INTERACT_DIST
			&& door_angle < INTERACT_ANGLE && print_message_sub(game, i))
			break ;
		i++;
	}
}
