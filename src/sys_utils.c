/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:40:44 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/10 19:18:08 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_debug(const char *str)
{
	struct timeval	current_time;

	if (!DEBUG_MODE)
		return ;
	gettimeofday(&current_time, NULL);
	printf(COLOR_C"[%ld] %s\n"COLOR_X, current_time.tv_sec, str);
}
