/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fillmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:58:46 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/15 11:17:25 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_setpath(char **line, const char *src)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	while (*src == ' ')
		src++;
	if (*src == '\0')
		*line = NULL;
	*line = ft_strdup(src);
	if (!*line)
		ft_exit_perror("Could not allocate memory for a texture path\n");
	(*line)[ft_strlen(src) - 1] = '\0';
}

/**
 * Takes a sting and sets the corresponding map texture or color path.
 * Returns 0 if the line was a valid texture/color line, 1 otherwise.
 */
static int	ft_checkline(const char *line)
{
	t_map	*map;

	map = &ft_game()->map;
	if (line[0] == '\n' || line[0] == '\0')
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (ft_setpath(&map->no, line + 2), 0);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (ft_setpath(&map->so, line + 2), 0);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (ft_setpath(&map->we, line + 2), 0);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (ft_setpath(&map->ea, line + 2), 0);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (ft_setpath(&map->f, line + 1), 0);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (ft_setpath(&map->c, line + 1), 0);
	return (1);
}

int	ft_initial_map_read(const char *src)
{
	int		fd;
	int		map_start[2];
	char	*line;

	fd = open (src, O_RDONLY);
	if (fd < 0)
		ft_exit_perror("Could not open the map file\n");
	map_start[0] = 0;
	map_start[1] = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_start[1] && ft_checkline(line))
			map_start[1] = 1;
		if (map_start[1] == 0)
			map_start[0]++;
		else
			ft_game()->map.h++;
		if (map_start[1] && (int)ft_strlen(line) > ft_game()->map.w)
			ft_game()->map.w = (int)ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map_start[0] * map_start[1]);
}

static void	ft_second_map_read_sub(int fd)
{
	int		i;
	char	*line;
	int		j;

	i = 0;
	while (i < ft_game()->map.h)
	{
		line = get_next_line(fd);
		ft_game()->map.tile[i] = malloc(ft_game()->map.w + 1);
		if (!ft_game()->map.tile[i])
			ft_exit_perror("Could not allocate memory for the map tile\n");
		j = -1;
		while (line && line[++j] && j < ft_game()->map.w && line[j] != '\n')
			ft_game()->map.tile[i][j] = line[j];
		while (j < ft_game()->map.w)
			ft_game()->map.tile[i][j++] = '0';
		ft_game()->map.tile[i][ft_game()->map.w] = '\0';
		free(line);
		i++;
	}
	ft_game()->map.tile[i] = NULL;
}

void	ft_second_map_read(const char *src, int map_start)
{
	int		fd;
	int		i;
	char	*line;

	fd = open (src, O_RDONLY);
	if (fd < 0)
		ft_exit_perror("Could not open the map file\n");
	ft_game()->map.tile = malloc(sizeof(char *) * (ft_game()->map.h + 1));
	if (!ft_game()->map.tile)
		ft_exit_perror("Could not allocate memory for the map\n");
	line = get_next_line(fd);
	i = 0;
	while (line && i < map_start - 1)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	ft_second_map_read_sub(fd);
	close(fd);
}
