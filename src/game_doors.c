/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:14:20 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/02 19:38:15 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*ft_get_door(int x, int y)
{
	t_gs	*game;
	int		i;

	game = ft_game();
	i = 0;
	while (i < game->max_doors)
	{
		if (game->doors[i].idx.u == y && game->doors[i].idx.v == x)
			return (&game->doors[i]);
		i++;
	}
	return (NULL);
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

void	try_open_doors(t_gs *game)
{
	t_player	*player;
	t_vec2		vec_door;
	float		door_angle;
	int			i;

	player = game->player;
	i = 0;
	while (i < game->door_count)
	{
		vec_door = (t_vec2){game->doors[i].sprite.pos.x - player->pos.x,
			game->doors[i].sprite.pos.y - player->pos.y};
		door_angle = fabsf(ft_angle_between_vec2(vec_door, player->lookdir));
		if (ft_vec2_length(vec_door) <= DOOR_OPEN_DIST
			&& door_angle < DOOR_OPEN_ANGLE)
		{
			if (!game->doors[i].key_needed || has_key(player))
			{
				if (!game->doors[i].is_opening)
					game->doors[i].is_opening = 1;
			}
		}
		i++;
	}
}

void	open_door(int i)
{
	t_door	*door;

	door = &ft_game()->doors[i];
	ft_calculate_sprite(ft_game()->view3d, &door->sprite);
	if (door->sprite.sp.dist < DOOR_OPEN_DIST && !door->closed)
		return ;
	if (!door->is_opening)
		return ;
	door->dt += door->is_opening * ft_game()->dt;
	if (door->closed && door->dt >= DOOR_OPEN_TIME)
	{
		door->closed = false;
	}
	if (door->dt >= 2 * DOOR_OPEN_TIME)
		door->is_opening = -1;
	if (door->is_opening == -1 && door->dt <= DOOR_OPEN_TIME)
		door->closed = true;
	if (door->dt <= 0.0f)
	{
		door->is_opening = 0;
		door->dt = 0.0f;
	}
}
