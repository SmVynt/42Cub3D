/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/14 11:43:39 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_check_map_complete(void)
{
	t_map	*map;

	map = &ft_game()->map;
	if (!map->no
		|| !map->so
		|| !map->we
		|| !map->ea
		|| !map->f
		|| !map->c)
		ft_exit_error("Map is missing some textures or colors\n");
}

static void	ft_checkfile(const char *src)
{
	int		map_start;

	map_start = ft_initial_map_read(src);
	printf(COLOR_G"Initial map read passed!\n"COLOR_X);
	ft_check_map_complete();
	printf(COLOR_G"Map is complete!\n"COLOR_X);
	if (map_start == 0)
		ft_exit_perror("Could not find a start of a map\n");
	ft_second_map_read(src, map_start);
	printf(COLOR_G"Second map read passed!\n"COLOR_X);
}

static void	ft_checkarguments(int argc, char **argv)
{
	if (argc != 2 || ft_strlen(argv[1]) < 5
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		ft_exit_error("Please run the game with this command:\
			\n./cub3d maps/<mapname.cub>\n");
	}
}

void	ft_printmap(t_map *map)
{
	int	i;

	printf(COLOR_G"Map width: %d, height: %d\n"COLOR_X, map->w, map->h);
	printf("NO: %s\n", map->no);
	printf("SO: %s\n", map->so);
	printf("WE: %s\n", map->we);
	printf("EA: %s\n", map->ea);
	printf("F: %s\n", map->f);
	printf("C: %s\n", map->c);
	printf(COLOR_G"Map:\n"COLOR_X);
	i = -1;
	while (map->tile && map->tile[++i])
		printf("%s\n", map->tile[i]);
}

static	void	ft_assign_textures(void)
{
	t_gs	*game;
	t_map	*map;

	game = ft_game();
	map = &game->map;
	ft_load_texture(map->no, &game->textures.no);
	ft_load_texture(map->so, &game->textures.so);
	ft_load_texture(map->we, &game->textures.we);
	ft_load_texture(map->ea, &game->textures.ea);
}

static uint32_t	ft_read_color(const char *color)
{
	int			i;
	int			j;
	int			num;
	uint32_t	res;

	i = 0;
	j = 0;
	res = 0xFF;
	while (i++ < 3)
	{
		num = 0;
		while(color[j] >= '0' && color[j] <= '9' && num <= 225)
		{
			num = num * 10 + color[j] - '0';
			j++;
		}
		if (num > 225)
			ft_exit_error("Wrong format of color\n");
		printf("Color %d: %d\n", i, num);
		res = res * 255 + num;
		// res = res << 8;
		// res = res | num;
		if (color[j] == ',' && i != 3)
			j++;
	}
	if (color[j])
		ft_exit_error("Wrong format of color\n");
	return (res);
}

static void	ft_assign_colors(void)
{
	t_gs	*game;
	t_map	*map;

	game = ft_game();
	map = &game->map;
	printf(COLOR_C"%s + %s\n"COLOR_X, map->f, map->c);
	game->render.top_color = ft_read_color(map->f);
	game->render.bottom_color = ft_read_color(map->c);
	printf(COLOR_C"%u + %u\n"COLOR_X, game->render.top_color, game->render.bottom_color);
}

void	ft_checkinput(int argc, char **argv)
{
	ft_checkarguments(argc, argv);
	ft_checkfile(argv[1]);
	// ft_printmap(&ft_game()->map);
	ft_assign_textures();
	ft_assign_colors();
	printf(COLOR_G"File check passed!\n"COLOR_X);
	ft_checkmap();
	printf(COLOR_Y"All checks passed!\n"COLOR_X);
}
