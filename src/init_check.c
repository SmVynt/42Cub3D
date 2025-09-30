/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/30 00:14:34 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		ft_exit("Map is missing some textures or colors\n");
}

static void	ft_checkfile(const char *src)
{
	int		map_start;

	map_start = ft_initial_map_read(src);
	ft_check_map_complete();
	if (map_start == 0)
		ft_exit_error("Could not find a start of a map\n");
	ft_second_map_read(src, map_start);
}

static void	ft_checkarguments(int argc, char **argv)
{
	if (argc != 2 || ft_strlen(argv[1]) < 5
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		ft_exit("Please run the game with this command:\
			\n./cub3d maps/<mapname.cub>\n");
	}
}

static void	ft_printmap(t_map *map)
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

void	ft_checkinput(int argc, char **argv)
{
	ft_checkarguments(argc, argv);
	ft_checkfile(argv[1]);
	ft_printmap(&ft_game()->map);
}
