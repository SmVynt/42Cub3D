/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_interact_message.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:25:29 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/13 20:44:06 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	hit_spec_wall(t_vec2 start, t_vec2 dir, int *side)
{
	t_vec2	curr;
	t_point	tile;

	curr.x = start.x + 0.5;
	curr.y = start.y + 0.5;
	while (true)
	{
		curr = get_next_wall_intersection(curr, dir, &tile, side);
		if (ft_is_wall((t_vec2){tile.u, tile.v}))
			break ;
	}
	return (ft_is_special_wall((t_vec2){tile.u, tile.v}, SPEC_WALL_CHARS));
}

bool	can_interact(t_door wall, int *side)
{
	t_vec2		wall_vec;
	double		wall_angle;
	t_player	*player;

	player = ft_game()->player;
	wall_vec = (t_vec2){wall.sprite.pos.x - player->pos.x,
		wall.sprite.pos.y - player->pos.y};
	wall_angle = fabs(ft_angle_between_vec2(wall_vec, player->lookdir));
	return (ft_vec2_length(wall_vec) < INTERACT_DIST
		&& wall_angle < INTERACT_ANGLE
		&& hit_spec_wall(player->pos, player->lookdir, side)
		&& (wall.is_switch || !wall.is_opening));
}

static void	update_switch_coord(t_sprite *sprite, int side)
{
	t_vec2		wall_vec;
	t_player	*player;

	player = ft_game()->player;
	wall_vec = (t_vec2){sprite->pos.x - player->pos.x,
		sprite->pos.y - player->pos.y};
	if (!side)
		sprite->pos.x -= ft_signd(wall_vec.x) * 0.5f;
	else
		sprite->pos.y -= ft_signd(wall_vec.y) * 0.5f;
}

static void	print_message_sub(t_gs *game, int i, int side)
{
	char	*msg;
	t_vec2	pos_backup;

	pos_backup = game->inter_walls[i].sprite.pos;
	if (game->inter_walls[i].is_switch)
	{
		msg = "[E] to interact";
		update_switch_coord(&game->inter_walls[i].sprite, side);
	}
	else
		msg = "[E] to open";
	ft_calculate_sprite(game->view3d, &game->inter_walls[i].sprite);
	game->inter_walls[i].sprite.pos = pos_backup;
	game->hints = mlx_put_string(game->mlx, msg,
			game->inter_walls[i].sprite.sp.screen_pos.x,
			game->inter_walls[i].sprite.sp.screen_pos.y
			+ game->player->lookupdown + 0.5 * game->player->jump_height
			* game->inter_walls[i].sprite.sp.max_size);
}

void	print_interact_msg(t_gs *game)
{
	int			i;
	int			side;

	if (game->hints)
		mlx_delete_image(game->mlx, game->hints);
	if (game->msg && mlx_get_time() - game->msg_time > 2)
		mlx_delete_image(game->mlx, game->msg);
	i = 0;
	while (i < game->inter_wall_count)
	{
		if (can_interact(game->inter_walls[i], &side))
		{
			print_message_sub(game, i, side);
			break ;
		}
		i++;
	}
}
