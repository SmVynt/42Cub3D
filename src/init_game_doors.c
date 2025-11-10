/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_doors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 17:17:52 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_doors(void)
{
	t_gs	*game;
	int		i;
	int		j;
	int		inter_wall_index;
	int		door_num;

	game = ft_game();
	if (game->max_doors == 0)
		return ;
	game->inter_walls = malloc(sizeof(t_door) * game->max_doors);
	if (!game->inter_walls)
		ft_exit_perror("Could not allocate memory for doors\n");
	inter_wall_index = 0;
	i = 0;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			door_num = ft_strchar_index(SPEC_WALL_CHARS, game->map.tile[i][j]);
			if (door_num != -1 && door_num < SPEC_TYPES_COUNT)
			{
				if (inter_wall_index >= game->max_doors)
					ft_exit_error("Item index out of bounds\n");
				game->inter_walls[inter_wall_index] = game->door_prefabs[door_num];
				game->inter_walls[inter_wall_index].idx.u = j;
				game->inter_walls[inter_wall_index].idx.v = i;
				game->inter_walls[inter_wall_index].closed = true;
				game->inter_walls[inter_wall_index].is_opening = false;
				game->inter_walls[inter_wall_index].dt = 0.0f;
				game->inter_walls[inter_wall_index].sprite.pos = (t_vec2){(float)j, (float)i};
				if (ft_strchar(SPEC_WALL_SWITCH, game->map.tile[i][j]) != NULL)
					game->inter_walls[inter_wall_index].is_switch = true;
				else
					game->inter_walls[inter_wall_index].is_switch = false;
				inter_wall_index++;
			}
			j++;
		}
		i++;
	}
	game->inter_wall_count = inter_wall_index;
	printf("Initialized %d interactive walls\n", game->inter_wall_count);
}
