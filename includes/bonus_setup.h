/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_setup.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:22:45 by nmikuka           #+#    #+#             */
/*   Updated: 2025/10/30 16:14:57 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_SETUP_H
# define BONUS_SETUP_H

# define ITEMS_TYPES_COUNT	4
# define MAP_ITEM_CHARS		"+K.#"
# define TEX_HEALTH			"textures/items/health_kit.png"
# define TEX_KEY			"textures/items/key.png"
# define TEX_CHANDELIER		"textures/items/chandelier.png"
# define TEX_BARREL			"textures/items/barrel.png"

# define CHARS_TYPES_COUNT	2
# define MAP_CHAR_CHARS		"as"
# define TEX_ALIEN			"textures/characters/alien.png"
# define TEX_SLIME			"textures/characters/slime.png"

# define DOORS_TYPES_COUNT	2
# define MAP_DOOR_CHARS		"dD"
# define TEX_DOOR			"textures/red_door.png"

# define WALLS_TYPES_COUNT	9
# define TEX_WALL_ATLAS		"textures/walls.png"
# define TEX_WALL_PLCHLDR	"textures/wall_placeholder.png"

# define UI_SCALE			2

# define MM_SIZE			150
# define MM_XSTART			10
# define MM_YSTART			10
# define MM_SCALE			12.0f
# define MM_COLOR_WALLS		0xFF00A9FF
# define MM_COLOR_DOORS		0xFF253ED4
# define MM_COLOR_HEALTH	0xFF89E21D
# define MM_COLOR_KEY		0xFF1E5EF2
# define MM_COLOR_ENEMIES	0xFF3000FF
# define MM_COLOR_EMPTY		0xFF090900

# define TEX_UI_MM			"textures/ui/T_MM_BG.png"

#endif
