/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:19:27 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/30 15:36:27 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit_error(char *str)
{
	printf(COLOR_R "Error\n" COLOR_Y);
	perror(str);
	printf("" COLOR_X);
	ft_clean();
	exit(EXIT_FAILURE);
}

void	ft_exit(char *str)
{
	printf(COLOR_R "Error\n" COLOR_Y);
	printf("%s"COLOR_X, str);
	ft_clean();
	exit(EXIT_FAILURE);
}
