/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:36:11 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/27 02:10:18 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42/MLX42.h"
# include "libft_mini.h"
# include "bonus_setup.h"

typedef struct s_point
{
	int	u;
	int	v;
}	t_point;

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_mat4
{
	float	m[4][4];
}	t_mat4;

typedef enum e_direction
{
	DIR_NO,
	DIR_EA,
	DIR_SO,
	DIR_WE
}	t_direction;

typedef struct s_map
{
	int		w;
	int		h;
	char	**tile;
	int		checked;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	t_point	start;
}	t_map;

typedef enum e_item_type
{
	IT_HEALTH,
	IT_KEY,
	IT_CHANDELIER,
	IT_BARREL
}	t_item_type;
// Don't forget to update ITEMS_TYPES_COUNT in structs.h

typedef enum e_char_type
{
	CH_ALIEN,
	CH_SLIME
}	t_char_type;
// Don't forget to update CHARS_TYPES_COUNT in structs.h

typedef struct s_sprite t_sprite;

typedef struct s_spriterender
{
	double		angle;
	double		dist;
	t_vec2		screen_pos;
	float		max_size;
	t_point		half_size;
	t_point		start;
	t_point		size;
	t_point		screen;
	bool		visible;
}	t_spriterender;

struct s_sprite
{
	mlx_texture_t	*texture;
	char			*path;
	float			bottom_offset;
	t_vec2			pos;
	t_spriterender	sp;
	t_sprite		*next;
};

typedef struct s_item
{
	t_item_type		type;
	t_sprite		sprite;
	bool			active;
	bool			pickupable;
	int				pickup_value;
}	t_item;

typedef struct s_char
{
	t_char_type		type;
	t_sprite		sprite;
	t_vec2			velocity;
	bool			alive;
	int				health;
	int				max_health;
}	t_char;

typedef struct s_door
{
	t_point idx;
	t_vec2	pos;
	int		is_opening;
	float	dt;
	t_sprite	sprite;
	bool	closed;
	bool	key_needed;
}	t_door;

typedef struct s_walltexture
{
	mlx_texture_t	*tex[4];
}	t_walltexture;

typedef struct s_textures
{
	// mlx_texture_t	*no;
	// mlx_texture_t	*so;
	// mlx_texture_t	*we;
	// mlx_texture_t	*ea;
	t_walltexture	wall;
	mlx_texture_t	*wall_atlas;
	t_walltexture	walls[WALLS_TYPES_COUNT];
	mlx_texture_t	*bg;
}	t_textures;

typedef struct s_render
{
	int			projection_plane_dist;
	float		*depth;
	uint32_t	top_color;
	uint32_t	bottom_color;
}	t_render;

typedef struct s_player
{
	t_vec2	pos;
	t_vec3	lookdir;
	t_point	mov_control;
	t_vec2	mouse_pos;
	t_vec2	mouse_diff;
	float	lookupdown;
	t_point	rot_control;
	bool	is_jumping;
	float	jump_height;
	float	jump_impuls;
	t_list	*pocket;
}	t_player;

typedef struct s_rayrender
{
	t_vec2		start;
	t_vec2		end;
	t_vec3		dir;
	int			bgx;
	double		angle;
	double		dist;
	// uint32_t	wall_dir;
	t_direction	wall_dir;
	char		wall_type;
	double		wall_height;
	bool		is_door;
	t_door		*door;
}	t_rayrender;

typedef struct s_gs
{
	t_player		*player;
	void			*mlx;
	void			*window;
	mlx_image_t		*minimap;
	mlx_image_t		*hud;
	mlx_image_t		*miniplayer;
	mlx_image_t		*view3d;
	mlx_image_t		*view3d_bg;
	t_map			map;
	t_textures		textures;
	t_render		render;
	t_sprite		*sh;
	t_item			item_prefabs[ITEMS_TYPES_COUNT];
	t_item			*items;
	int				item_count;
	int				max_items;
	t_char			char_prefabs[CHARS_TYPES_COUNT];
	t_char			*chars;
	int				char_count;
	int				max_chars;
	t_door			door_prefabs[DOORS_TYPES_COUNT];
	t_door			*doors;
	int				door_count;
	int				max_doors;
	float			dt;
}	t_gs;

// typedef struct s_texture
// {
// 	void	*src;
// 	int		w;
// 	int		h;
// }	t_texture;

// typedef struct s_animation	t_animation;

// typedef struct s_animation
// {
// 	t_texture	*src;
// 	int			frame;
// 	int			frame_count;
// 	int			frame_time;
// 	int			delta;
// 	t_animation	*next;
// }	t_animation;

// typedef struct s_anim_list
// {
// 	t_animation	*current;
// 	t_animation	idle;
// 	t_animation	move;
// 	t_animation	change;
// 	t_animation	idle2;
// }	t_anim_list;

// typedef struct s_textures
// {
// 	t_texture	bg;
// 	t_texture	tileset;
// 	t_texture	tiles[16];
// 	t_texture	hero_idle[4];
// 	t_texture	hero_move[4];
// 	t_texture	hero_death[4];
// 	t_texture	enemy_idle[4];
// 	t_texture	enemy_move[4];
// 	t_texture	enemy_death[4];
// 	t_texture	coll_idle[4];
// 	t_texture	coll_take[4];
// 	t_texture	coll_idle2[4];
// 	t_texture	exit_idle[4];
// 	t_texture	exit_open[5];
// 	t_texture	exit_idle2[4];
// 	t_texture	erasor;
// 	t_texture	erasor_sm;
// 	t_texture	decor_8[16];
// 	t_texture	decor_16[16];
// 	t_texture	digits[10];
// 	t_texture	screen_won;
// 	t_texture	screen_lost;
// 	t_texture	temp;
// }	t_textures;

// typedef struct s_hero
// {
// 	int			x;
// 	int			y;
// 	int			x_next;
// 	int			y_next;
// 	int			x_prev;
// 	int			y_prev;
// 	int			wish_x;
// 	int			wish_y;
// 	int			alive;
// 	int			state;
// 	int			flipped;
// 	t_anim_list	anim;
// }	t_hero;

// typedef struct s_enemy
// {
// 	int			x;
// 	int			y;
// 	int			x_dest;
// 	int			y_dest;
// 	int			x_next;
// 	int			y_next;
// 	int			x_prev;
// 	int			y_prev;
// 	int			flipped;
// 	int			state;
// 	t_anim_list	anim;
// }	t_enemy;

// typedef struct s_collect
// {
// 	int			x;
// 	int			y;
// 	int			active;
// 	int			state;
// 	int			flipped;
// 	t_anim_list	anim;
// }	t_collect;

// typedef struct s_exit
// {
// 	int			x;
// 	int			y;
// 	int			active;
// 	int			state;
// 	t_anim_list	anim;
// }	t_exit;

// typedef struct s_count
// {
// 	int	collectibles;
// 	int	exit;
// 	int	start;
// 	int	enemies;
// }	t_count;

// typedef struct s_alloc
// {
// 	int		map;
// 	int		enemies;
// 	int		collects;
// }	t_alloc;

// typedef struct s_imgdt
// {
// 	int		bpp;
// 	int		size_line;
// 	int		endian;
// 	char	*data;
// }	t_imgdt;

// typedef struct s_render
// {
// 	t_texture	bg;
// 	t_texture	decor;
// 	t_texture	en;
// 	t_texture	fg;
// 	t_texture	render_sm;
// 	t_texture	render;
// }	t_render;


#endif
