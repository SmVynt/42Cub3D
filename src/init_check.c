/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/26 17:17:44 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void ft_checkfile(const char *src)
{
	int fd;

	fd = open (src, O_RDONLY);
	if (fd < 0)
		ft_exit_error("Could not open the map file\n");
}

static void ft_checkarguments(int argc, char **argv)
{
	if (argc != 2 || ft_strlen(argv[1]) < 5
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4) != 0)
	{
		ft_exit("Please run the game with this command:\
			\n./cub3d maps/<mapname.ber>\n");
	}
}

void	ft_checkinput(int argc, char **argv)
{
	ft_checkarguments(argc, argv);
	ft_checkfile(argv[1]);
}
