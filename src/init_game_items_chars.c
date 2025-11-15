/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_items_chars.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/15 16:34:10 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_set_items_check(int *item_index)
{
	t_gs	*game;
	int		i;
	int		j;
	int		item_num;

	game = ft_game();
	i = -1;
	while (++i < game->map.h)
	{
		j = -1;
		while (++j < game->map.w)
		{
			item_num = ft_strchar_index(MAP_ITEM_CHARS, game->map.tile[i][j]);
			if (item_num != -1 && item_num < ITEMS_TYPES_COUNT)
			{
				if (*item_index >= game->item_count)
					ft_exit_error("Item index out of bounds\n");
				game->items[*item_index] = game->prefabs.items[item_num];
				game->items[*item_index].sprite.pos
					= (t_vec2){(double)j, (double)i};
				(*item_index)++;
			}
		}
	}
}

void	ft_set_items(void)
{
	t_gs	*game;
	int		item_index;

	game = ft_game();
	if (game->item_count == 0)
		return ;
	game->items = malloc(sizeof(t_item) * game->item_count);
	if (!game->items)
		ft_exit_perror("Could not allocate memory for items\n");
	item_index = 0;
	ft_set_items_check(&item_index);
	game->item_count = item_index;
	printf("Initialized %d items\n", game->item_count);
}

static void	ft_set_chars_check(int *char_index)
{
	t_gs	*game;
	int		i;
	int		j;
	int		char_num;

	game = ft_game();
	i = -1;
	while (++i < game->map.h)
	{
		j = -1;
		while (++j < game->map.w)
		{
			char_num = ft_strchar_index(MAP_CHAR_CHARS, game->map.tile[i][j]);
			if (ft_strchar(MAP_CHAR_CHARS, game->map.tile[i][j]) != NULL
				&& char_num != -1 && char_num < CHARS_TYPES_COUNT)
			{
				if (*char_index >= game->char_count)
					ft_exit_error("Char index out of bounds\n");
				game->chars[*char_index] = game->prefabs.chars[char_num];
				game->chars[*char_index].sprite.pos
					= (t_vec2){(double)j, (double)i};
				(*char_index)++;
			}
		}
	}
}

void	ft_set_chars(void)
{
	t_gs	*game;
	int		char_index;

	game = ft_game();
	if (game->char_count == 0)
		return ;
	game->chars = malloc(sizeof(t_char) * game->char_count);
	if (!game->chars)
		ft_exit_perror("Could not allocate memory for chars\n");
	char_index = 0;
	ft_set_chars_check(&char_index);
	game->char_count = char_index;
	printf("Initialized %d chars\n", game->char_count);
}
