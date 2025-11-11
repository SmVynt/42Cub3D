/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check_tex_colors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 21:38:29 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_assign_textures(void)
{
	t_gs	*game;
	t_map	*map;

	game = ft_game();
	map = &game->map;
	ft_load_texture(map->no, &game->textures.walls[0].tex[DIR_NO]);
	ft_load_texture(map->so, &game->textures.walls[0].tex[DIR_SO]);
	ft_load_texture(map->we, &game->textures.walls[0].tex[DIR_WE]);
	ft_load_texture(map->ea, &game->textures.walls[0].tex[DIR_EA]);
	ft_load_texture("textures/BG.png", &game->textures.bg);
}

static uint32_t	ft_read_color(const char *color)
{
	int			i;
	int			j;
	uint32_t	num;
	uint32_t	res;

	i = 0;
	j = 0;
	res = 0xFF000000;
	while (i++ < 3)
	{
		num = 0;
		while (color[j] >= '0' && color[j] <= '9' && num <= 255)
			num = num * 10 + color[j++] - '0';
		if (num > 255)
			ft_exit_error("Wrong format of color\n");
		num <<= ((i - 1) * 8);
		res |= num;
		if (color[j] == ',' && i != 3)
			j++;
	}
	if (color[j])
		ft_exit_error("Wrong format of color\n");
	return (res);
}

void	ft_assign_colors(void)
{
	t_gs	*game;
	t_map	*map;

	game = ft_game();
	map = &game->map;
	game->render.top_color = ft_read_color(map->c);
	game->render.bottom_color = ft_read_color(map->f);
}
