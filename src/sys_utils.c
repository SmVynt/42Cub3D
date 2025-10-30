/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:40:44 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/30 12:42:40 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	print_debug(const char *str)
{
	if (DEBUG_MODE)
		printf(COLOR_C"[DEBUG] %s\n"COLOR_X, str);
}
