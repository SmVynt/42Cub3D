/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/09 16:57:35 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_load_texture(const char *path, mlx_texture_t **texture)
{
	*texture = mlx_load_png(path);
	if (!*texture)
		ft_exit_perror("Failed to load texture\n");
	printf(COLOR_G"Loaded texture %s (w: %d, h: %d)\n"COLOR_X, path, (*texture)->width, (*texture)->height);
}
