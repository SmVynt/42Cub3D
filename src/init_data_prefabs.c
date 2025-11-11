/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_prefabs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:45:35 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/11 11:11:36 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_prefabs(void)
{
	t_gs	*game;

	game = ft_game();
	ft_init_prefabs_items(game);
	ft_init_prefabs_chars(game);
	ft_init_prefabs_interacts(game);
}
