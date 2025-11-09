/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_setup.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:22:45 by nmikuka           #+#    #+#             */
/*   Updated: 2025/11/05 15:47:06 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_SETUP_H
# define BONUS_SETUP_H

# define MAX_HP				100.0f

# define ITEMS_TYPES_COUNT	6
# define MAP_ITEM_CHARS		"+K.bfm"
# define TEX_HEALTH			"textures/items/it_health_kit.png"
# define TEX_KEY			"textures/items/it_key.png"
# define TEX_CHANDELIER		"textures/items/it_chandelier.png"
# define TEX_BARREL			"textures/items/it_barrel.png"
# define TEX_FIRE			"textures/items/it_fire.png"
# define TEX_MAP			"textures/items/it_map.png"

# define CHARS_TYPES_COUNT	2
# define MAP_CHAR_CHARS		"as"
# define TEX_ALIEN			"textures/characters/e_jellyfish.png"
# define TEX_SLIME			"textures/characters/e_blob.png"
# define AI_SPEED_ALIEN		1.5f
# define AI_SPEED_SLIME		1.0f
# define AI_TIMER			0.1f
# define AI_CONTACT_DIST	0.3f
# define AI_DAMAGE_PER_SEC	100.0f

# define LAV_DAMAGE_PER_SEC	300.0f

# define DOORS_TYPES_COUNT	2
# define MAP_DOOR_CHARS		"dD"
# define TEX_DOOR			"textures/red_door.png"

# define WALLS_TYPES_COUNT	10
# define TEX_WALL_ATLAS		"textures/t_walls.png"
# define TEX_WALL_PLCHLDR	"textures/t_wall_placeholder.png"

# define SPEC_TYPES_COUNT	4
# define SPEC_WALL_CHARS	"dD67"
# define SPEC_WALL_FADE		"8:"
# define SPEC_WALL_SWITCH	"67"

# define FLOOR_TYPE_COUNT	4
# define TEX_FLOOR_ATLAS	"textures/t_floor.png"

# define CEILING_TYPE_COUNT	4
# define TEX_CEILING_ATLAS	"textures/t_ceiling.png"

# define UI_SCALE			2

# define MAX_HOR_SHAKING	0.1
# define MAX_VERT_SHAKING	0.8
# define SHAKING_TIME		0.6

# define MM_SIZE			150
# define MM_XSTART			10
# define MM_YSTART			10
# define MM_SCALE			12.0f
# define MM_ANIM_SPEED		10.0f
# define MM_COLOR_WALLS		0xFF00A9FF
# define MM_COLOR_DOORS		0xFF253ED4
# define MM_COLOR_HEALTH	0xFF89E21D
# define MM_COLOR_KEY		0xFF1E5EF2
# define MM_COLOR_ENEMIES	0xFF3000FF
# define MM_COLOR_EMPTY		0xFF090900

# define UI_HP_BAR_XSCALE	0.8f
# define UI_HP_BAR_YSCALE	0.5f

# define TEX_UI_MM			"textures/ui/T_MM_FG.png"
# define TEX_UI_HEALTH		"textures/ui/T_HP_FG.png"

# define TEX_DEFEAT			"textures/end_screens/defeat.png"
# define TEX_VICTORY		"textures/end_screens/victory.png"

#endif
