/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:14:20 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/15 16:24:01 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*ft_get_door(int x, int y)
{
	t_gs	*game;
	int		i;

	game = ft_game();
	i = 0;
	while (i < game->inter_wall_count)
	{
		if (game->inter_walls[i].idx.u == y && game->inter_walls[i].idx.v == x)
			return (&game->inter_walls[i]);
		i++;
	}
	return (NULL);
}

void	open_door(int i)
{
	t_door	*door;

	door = &ft_game()->inter_walls[i];
	ft_calculate_sprite(ft_game()->view3d, &door->sprite);
	if (door->sprite.sp.dist < INTERACT_DIST && !door->closed)
		return ;
	if (!door->is_opening)
		return ;
	door->dt += door->is_opening * ft_game()->dt;
	if (door->closed && door->dt >= DOOR_OPEN_TIME)
		door->closed = false;
	if (door->dt >= 2 * DOOR_OPEN_TIME)
		door->is_opening = -1;
	if (door->is_opening == -1 && door->dt <= DOOR_OPEN_TIME)
	{
		if (!door->closed)
			audio_play(ft_game()->audio.door_sound);
		door->closed = true;
	}
	if (door->dt <= 0.0)
	{
		door->is_opening = 0;
		door->dt = 0.0;
	}
}
