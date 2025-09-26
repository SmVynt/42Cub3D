/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:05:05 by psmolin           #+#    #+#             */
/*   Updated: 2025/09/26 12:54:27 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "mlx/mlx.h"
// # include "lbs/gnl/get_next_line.h"
// # include "lbs/printf/ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define COLOR_R "\033[31m"
# define COLOR_G "\033[32m"
# define COLOR_Y "\033[33m"
# define COLOR_B "\033[34m"
# define COLOR_M "\033[35m"
# define COLOR_C "\033[36m"
# define COLOR_W "\033[37m"
# define COLOR_BOLD "\033[1m"
# define COLOR_X "\033[0m"

# define TS 32
# define SCALE 3
# define FRAME_TIME 4
# define MOVE_SPEED 0.2f
# define GAME_LERP 0.45f

# define STATE_IDLE 0
# define STATE_MOVE 1
# define STATE_DEATH 2
# define STATE_HERO 3
# define STATE_ENEMIES 4
# define STATE_FINAL 5
# define STATE_WON 6
# define STATE_LOST 7
# define STATE_CALC 8
# define STATE_CALC2 9

# define PATH_TILES "./textures/bg_tileset_02.xpm"
# define PATH_HERO_IDLE "./textures/hero_idle.xpm"
# define PATH_HERO_MOVE "./textures/hero_run.xpm"
# define PATH_ENEMY_IDLE "./textures/enemy_idle.xpm"
# define PATH_ENEMY_MOVE "./textures/enemy_move.xpm"
# define PATH_ERASOR "./textures/erasor.xpm"
# define PATH_DECOR_8 "./textures/decor_8.xpm"
# define PATH_DECOR_16 "./textures/decor_16.xpm"
# define PATH_EXIT_O "./textures/exit_opened.xpm"
# define PATH_EXIT_C "./textures/exit_closed.xpm"
# define PATH_EXIT_OP "./textures/exit_open.xpm"
# define PATH_CRYSTAL "./textures/crystal.xpm"
# define PATH_CRYSTAL_TAKE "./textures/crystal_take.xpm"
# define PATH_DIGITS "./textures/t_digits_x2.xpm"
# define PATH_SCREEN_WON "./textures/screen_won.xpm"
# define PATH_SCREEN_LOST "./textures/screen_lost.xpm"

# define C_W '1'
# define C_E '0'
# define C_P 'P'
# define C_EN 'X'
# define C_C 'C'
# define C_EX 'E'

typedef struct s_vec
{
	int	x;
	int	y;
}	t_vec;

typedef struct s_map
{
	int		w;
	int		h;
	char	**tile;
	int		checked;
}	t_map;

typedef struct s_texture
{
	void	*src;
	int		w;
	int		h;
}	t_texture;

typedef struct s_animation	t_animation;

typedef struct s_animation
{
	t_texture	*src;
	int			frame;
	int			frame_count;
	int			frame_time;
	int			delta;
	t_animation	*next;
}	t_animation;

typedef struct s_anim_list
{
	t_animation	*current;
	t_animation	idle;
	t_animation	move;
	t_animation	change;
	t_animation	idle2;
}	t_anim_list;

typedef struct s_textures
{
	t_texture	bg;
	t_texture	tileset;
	t_texture	tiles[16];
	t_texture	hero_idle[4];
	t_texture	hero_move[4];
	t_texture	hero_death[4];
	t_texture	enemy_idle[4];
	t_texture	enemy_move[4];
	t_texture	enemy_death[4];
	t_texture	coll_idle[4];
	t_texture	coll_take[4];
	t_texture	coll_idle2[4];
	t_texture	exit_idle[4];
	t_texture	exit_open[5];
	t_texture	exit_idle2[4];
	t_texture	erasor;
	t_texture	erasor_sm;
	t_texture	decor_8[16];
	t_texture	decor_16[16];
	t_texture	digits[10];
	t_texture	screen_won;
	t_texture	screen_lost;
	t_texture	temp;
}	t_textures;

typedef struct s_hero
{
	int			x;
	int			y;
	int			x_next;
	int			y_next;
	int			x_prev;
	int			y_prev;
	int			wish_x;
	int			wish_y;
	int			alive;
	int			state;
	int			flipped;
	t_anim_list	anim;
}	t_hero;

typedef struct s_enemy
{
	int			x;
	int			y;
	int			x_dest;
	int			y_dest;
	int			x_next;
	int			y_next;
	int			x_prev;
	int			y_prev;
	int			flipped;
	int			state;
	t_anim_list	anim;
}	t_enemy;

typedef struct s_collect
{
	int			x;
	int			y;
	int			active;
	int			state;
	int			flipped;
	t_anim_list	anim;
}	t_collect;

typedef struct s_exit
{
	int			x;
	int			y;
	int			active;
	int			state;
	t_anim_list	anim;
}	t_exit;

typedef struct s_count
{
	int	collectibles;
	int	exit;
	int	start;
	int	enemies;
}	t_count;

typedef struct s_alloc
{
	int		map;
	int		enemies;
	int		collects;
}	t_alloc;

typedef struct s_imgdt
{
	int		bpp;
	int		size_line;
	int		endian;
	char	*data;
}	t_imgdt;

typedef struct s_render
{
	t_texture	bg;
	t_texture	decor;
	t_texture	en;
	t_texture	fg;
	t_texture	render_sm;
	t_texture	render;
}	t_render;

typedef struct s_gs
{
	void		*mlx;
	void		*window;
	t_render	img;
	t_map		map;
	float		turn;
	int			steps;
	int			state;
	t_exit		exit;
	t_enemy		*enemies;
	t_collect	*collects;
	int			collected;
	t_hero		hero;
	t_count		c;
	t_alloc		alloc;
	t_textures	textures;
}	t_gs;

// void	ft_exit_error(char *str, t_gs *game);
// void	ft_exit(char *str, t_gs *game);
// int		ft_exit_game(t_gs *game);
// void	ft_createhooks(t_gs *game);
// void	ft_checkinput(int argc, char **argv, t_gs *game);

// void	ft_init_image(char *path, t_texture *texture, t_gs *game);
// void	ft_init_images(t_gs *game);
// void	ft_init_animations(t_gs *game);
// void	ft_init_animation(char *path,
// 			t_texture *texture, t_animation *anim, t_gs *game);
// void	ft_init_tileset(t_gs *game);
// void	ft_init_texture(t_texture *texture, t_gs *game, int w, int h);
// void	ft_init_set(char *path, t_texture *texture, t_gs *game);
// void	ft_init_hero(t_gs *game);
// void	ft_init_enemies(t_gs *game);
// void	ft_init_objs(t_gs *game);
// void	ft_restart(t_gs *game);
// void	ft_initialize(t_gs *game, char **argv);

// void	ft_check_map(t_gs *game);
// void	ft_flood_fill(t_map *map, char start);
// void	ft_fill_tilemap(t_gs *game);

// int		ft_update(t_gs *game);
// void	ft_update_enemies(t_gs *game);
// void	ft_update_hero(t_gs *game);
// void	ft_update_objs(t_gs *game);
// void	ft_update_exit(t_gs *game);
// void	ft_update_count(t_gs *game);

// void	ft_find_next_spot(t_gs *game, t_enemy *enemy);

// void	ft_next_frame_to_img(t_texture *target,
// 			t_anim_list *anim_list, t_vec v, int f);
// void	ft_next_frame_to_img_cover(t_texture *target,
// 			t_anim_list *anim_list, t_vec v, int f);

// void	ft_scale_image(t_texture *src, t_texture *dst);
// void	ft_scale_image_ca(t_texture *src, t_texture *dst);
// void	ft_override_images(t_texture *dst, t_texture *src, t_vec v, int f);
// void	ft_cover_images(t_texture *dst, t_texture *src, t_vec v, int f);
// void	ft_copy_pixel(char *dst, char *src);
// void	ft_cover_pixel(char *dst, char *src);
// void	ft_clean_texture(t_texture *dst);

// int		get_rgba(int r, int g, int b, int a);
// int		get_r(int rgba);
// int		get_g(int rgba);
// int		get_b(int rgba);
// int		get_a(int rgba);

// t_imgdt	get_img_data(void *img);

// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// size_t	ft_strlcpy(char *dst, const char *src, size_t size);
// t_vec	mk_vec(int x, int y);
// int		ft_lerp_int(int a, int b, float t);
// float	ft_lerp(float a, float b, float t);
// int		ft_tol(int a, int b);
// int		ft_random(int min, int max);
// int		ft_min(int a, int b);
// int		ft_max(int a, int b);
// int		ft_dir(int a, int b);
// char	*ft_strip_from_n(char *str);
// t_map	*ft_copy_map(t_map *src);
// void	ft_free_map(t_map *map);
// void	ft_allocate_map(t_map *map, t_gs *game);

// void	ft_update_end(t_gs *game);

#endif
