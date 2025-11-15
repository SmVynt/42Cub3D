/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_doors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/15 16:33:54 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_door_check(int i, int j, int *inter_wall_index)
{
	t_gs	*game;
	int		door_num;
	int		iwi;

	game = ft_game();
	iwi = *inter_wall_index;
	door_num = ft_strchar_index(SPEC_WALL_CHARS, game->map.tile[i][j]);
	if (door_num != -1 && door_num < SPEC_TYPES_COUNT)
	{
		if (iwi >= game->inter_wall_count)
			ft_exit_error("Item index out of bounds\n");
		game->inter_walls[iwi] = game->prefabs.doors[door_num];
		game->inter_walls[iwi].idx.u = j;
		game->inter_walls[iwi].idx.v = i;
		game->inter_walls[iwi].closed = true;
		game->inter_walls[iwi].is_opening = false;
		game->inter_walls[iwi].dt = 0.0;
		game->inter_walls[iwi].sprite.pos = (t_vec2){(double)j, (double)i};
		if (ft_strchar(SPEC_WALL_SWITCH, game->map.tile[i][j]) != NULL)
			game->inter_walls[iwi].is_switch = true;
		else
			game->inter_walls[iwi].is_switch = false;
		(*inter_wall_index)++;
	}
}

void	ft_set_doors(void)
{
	t_gs	*game;
	int		i;
	int		j;
	int		inter_wall_index;

	game = ft_game();
	if (game->inter_wall_count == 0)
		return ;
	game->inter_walls = malloc(sizeof(t_door) * game->inter_wall_count);
	if (!game->inter_walls)
		ft_exit_perror("Could not allocate memory for doors\n");
	inter_wall_index = 0;
	i = 0;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			ft_set_door_check(i, j, &inter_wall_index);
			j++;
		}
		i++;
	}
	game->inter_wall_count = inter_wall_index;
}
