/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_interact.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:25:29 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/13 20:31:44 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	toggle_switch(t_door *inter_switch)
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

static void	swap_chars(char from, char to)
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

static void	interact_sub(t_gs *game, int i)
{
	t_player	*player;

	player = game->player;
	if (game->inter_walls[i].is_switch)
	{
		toggle_switch(&game->inter_walls[i]);
		swap_chars('8', '#');
		game->player->is_shaking = true;
		game->player->shaking_start = mlx_get_time();
	}
	else if (!game->inter_walls[i].key_needed || has_key(player))
		game->inter_walls[i].is_opening = 1;
	else
	{
		if (game->msg)
			mlx_delete_image(game->mlx, game->msg);
		game->msg = mlx_put_string(game->mlx,
				"Door is closed. Key needed!", game->view3d->height
				- 200, game->view3d->height - 100);
		game->msg_time = mlx_get_time();
	}
}

void	interact(t_gs *game)
{
	int			side;
	int			i;

	i = 0;
	while (i < game->inter_wall_count)
	{
		if (can_interact(game->inter_walls[i], &side))
			interact_sub(game, i);
		i++;
	}
}
