/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_items_chars.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 17:27:45 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_items(void)
{
	t_gs	*game;
	int		i;
	int		j;
	int		item_index;
	int		item_num;

	game = ft_game();
	if (game->max_items == 0)
		return ;
	game->items = malloc(sizeof(t_item) * game->max_items);
	if (!game->items)
		ft_exit_perror("Could not allocate memory for items\n");
	item_index = 0;
	i = 0;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			item_num = ft_strchar_index(MAP_ITEM_CHARS, game->map.tile[i][j]);
			if (item_num != -1 && item_num < ITEMS_TYPES_COUNT)
			{
				if (item_index >= game->max_items)
					ft_exit_error("Item index out of bounds\n");
				game->items[item_index] = game->item_prefabs[item_num];
				game->items[item_index].sprite.pos = (t_vec2){(float)j, (float)i};
				item_index++;
			}
			j++;
		}
		i++;
	}
	game->item_count = item_index;
	printf("Initialized %d items\n", game->item_count);
}

void	ft_set_chars(void)
{
	t_gs	*game;
	int		i;
	int		j;
	int		char_index;
	int		char_num;

	game = ft_game();
	if (game->max_chars == 0)
		return ;
	game->chars = malloc(sizeof(t_char) * game->max_chars);
	if (!game->chars)
		ft_exit_perror("Could not allocate memory for chars\n");
	char_index = 0;
	i = 0;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			char_num = ft_strchar_index(MAP_CHAR_CHARS, game->map.tile[i][j]);
			if (ft_strchar(MAP_CHAR_CHARS, game->map.tile[i][j]) != NULL && char_num != -1 && char_num < CHARS_TYPES_COUNT)
			{
				if (char_index >= game->max_chars)
					ft_exit_error("Char index out of bounds\n");
				game->chars[char_index] = game->char_prefabs[char_num];
				game->chars[char_index].sprite.pos = (t_vec2){(float)j, (float)i};
				char_index++;
			}
			j++;
		}
		i++;
	}
	game->char_count = char_index;
	printf("Initialized %d chars\n", game->char_count);
}
