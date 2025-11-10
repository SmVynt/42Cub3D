/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:40:44 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 21:31:29 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_debug(const char *str)
{
	double	current_time;

	if (!DEBUG_MODE)
		return ;
	current_time = mlx_get_time();
	printf(COLOR_C"[%f] %s\n"COLOR_X, current_time, str);
}
