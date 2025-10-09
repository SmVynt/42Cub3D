/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:36:11 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/06 20:40:15 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42/MLX42.h"

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

typedef struct s_player
{
	t_vec2	pos;
	t_vec3	lookdir;
	t_point	mov_control;
	float	mouse_x;
	float	mouse_dx;
	int	rot_control;
}	t_player;

typedef struct s_gs
{
	t_player	*player;
	void		*mlx;
	void		*window;
	mlx_image_t	*minimap;
	mlx_image_t	*miniplayer;
	mlx_image_t	*view3d;
	t_map		map;
	int			state;
	int			collected;
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
