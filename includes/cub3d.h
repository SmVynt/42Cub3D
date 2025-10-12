/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:05:05 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/12 11:33:09 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "../lib/gnl/get_next_line.h"
// # include "lib/gnl/get_next_line.h"
// # include "lib/printf/ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <sys/time.h>
# include "structs.h"
# include "libft_mini.h"
# include "ft_mat4.h"

# define WIDTH		1280
# define HEIGHT		720

# define COLOR_WHITE	0xFFFFFFFF
# define COLOR_BLACK	0xFF000000
# define COLOR_RED		0xFF0000FF
# define COLOR_GREEN	0xFF00FF00
# define COLOR_BLUE		0xFFFF0000
# define COLOR_YELLOW	0xFF00FFFF
# define COLOR_GREY		0xFF00FFFF

# define COLOR_R		"\033[31m"
# define COLOR_G		"\033[32m"
# define COLOR_Y		"\033[33m"
# define COLOR_B		"\033[34m"
# define COLOR_M		"\033[35m"
# define COLOR_C		"\033[36m"
# define COLOR_W		"\033[37m"
# define COLOR_BOLD		"\033[1m"
# define COLOR_X		"\033[0m"

# define MAP_ALLOWED_CHARS		"0123456789NSEW "
# define MAP_WALL_CHARS			"123456789"
# define MAP_PLAYER_CHARS		"NSEW"

# define MAP_SCALE				10
# ifndef M_PI
#  define M_PI					3.14159265358979323846
# endif
# define PI						3.14159265358
# define TWO_PI					6.28318530718
# define DEG_TO_RAD				0.01745329251
# define RAD_TO_DEG				57.2957795131
# define FOV					60.0f
# define FOV_RAD				M_PI / 3
# define PIXEL_SIZE				4
# define TARGET_FPS				60.0f
# define MAX_DT					0.05f
# define PLAYERSPEED			6.0f
# define ROTATIONSPEED			2.0f
# define MOUSE_SENS				0.5f

// Fast inline pixel setting
#define PUT_PIXEL_FAST(image, x, y, color) \
	if ((unsigned int)(x) < (image)->width && (unsigned int)(y) < (image)->height) \
		((uint32_t *)(image)->pixels)[(y) * (image)->width + (x)] = (color)

void	ft_initialize(void);

int		ft_initial_map_read(const char *src);
void	ft_second_map_read(const char *src, int map_start);
void	ft_checkinput(int argc, char **argv);
void	ft_checkmap(void);
void	ft_printmap(t_map *map);

void	ft_setgame(void);

t_gs	*ft_game(void);

void	ft_free_and_null(void *ptr);
void	ft_clean(void);

void	ft_exit_perror(char *str);
void	ft_exit_error(char *str);
void	ft_exit(void);


// t_player	*init_player(char **map, int w, int h);
void	ft_load_texture(const char *path, mlx_texture_t **texture);

void 	put_pixel(mlx_image_t *image, t_point pos, uint32_t color);
void	draw_line_ray(mlx_image_t *image, t_point p0, t_vec3 lookdir, t_map map, int x);
void	draw_wall(mlx_image_t *image, t_vec2 point, t_vec3 lookdir, int x);
int		ft_is_wall(t_vec2 p);
// void	init_player(void);

void	draw(int32_t width, int32_t height, void *param);
void	draw_map(mlx_image_t *image, t_map *map);
void	draw_player(mlx_image_t *image);
void	draw_walls(mlx_image_t *image);
void	draw_square(mlx_image_t *image, int size, t_point pos, uint32_t color);
void	draw_map_square(mlx_image_t *image, t_point pos, uint32_t color);
void	draw_circle(mlx_image_t *image, t_point center, int radius, uint32_t color);
void	draw_line(mlx_image_t *image, t_point start, t_point end, uint32_t color);

uint32_t	ft_get_pixel_color(mlx_texture_t *texture, t_point pixel);
int			ft_get_tex_coord(float x, int texture_width);

void	ft_createhooks(void);
void	ft_update(void *param);
void	ft_update_minimap(void *param);
// void	ft_update_view3d(void *param);
void	ft_update_player(void);
void	ft_update_graphics(void);

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
