/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:05:05 by psmolin           #+#    #+#             */
/*   Updated: 2025/10/30 16:30:10 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "../lib/gnl/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <sys/time.h>
# include "structs.h"
# include "ft_mat4.h"

# define DEBUG_MODE	true

# define WIDTH		1280
# define HEIGHT		720

# define COLOR_WHITE	0xFFFFFFFF
# define COLOR_BLACK	0xFF000000
# define COLOR_RED		0xFF0000FF
# define COLOR_GREEN	0xFF00FF00
# define COLOR_BLUE		0xFFFF0000
# define COLOR_YELLOW	0xFF00FFFF
# define COLOR_GREY		0xFF00FFFF
# define COLOR_RED_TRANSP	0xFF00001A

# define COLOR_R		"\033[31m"
# define COLOR_G		"\033[32m"
# define COLOR_Y		"\033[33m"
# define COLOR_B		"\033[34m"
# define COLOR_M		"\033[35m"
# define COLOR_C		"\033[36m"
# define COLOR_W		"\033[37m"
# define COLOR_BOLD		"\033[1m"
# define COLOR_X		"\033[0m"

# define MAP_ALLOWED_CHARS		"0123456789NSEW +.K#asdD"
# define MAP_WALL_CHARS			"123456789"
# define MAP_PLAYER_CHARS		"NSEW"

# define MAP_SCALE				10
# ifndef M_PI
#  define M_PI					3.14159265358979323846
# endif
# define PI						3.14159265358
# define TWO_PI					6.28318530718
# define HALF_PI				1.57079632679
# define DEG_TO_RAD				0.01745329251
# define RAD_TO_DEG				57.2957795131
# define FOV					60.0f
# define FOV_RAD				(M_PI / 3.0)
# define PIXEL_SIZE				2
# define STANDARD_SPRITE_SIZE	64
# define JUMP_HEIGHT			1.0f
# define JUMP_IMPULSE			3.2f
# define GRAVITY				9.8f
# define TILE_BORDER			0.1f
# define TARGET_FPS				60.0f
# define MAX_DT					0.05f
# define DOOR_OPEN_TIME			1.0f
# define DOOR_OPEN_DIST			2.0f
# define DOOR_OPEN_ANGLE		(M_PI / 3.0f)
# define PLAYERSPEED			6.0f
# define ROTATIONSPEED			2.0f
# define MOUSE_XSENS			0.5f
# define MOUSE_YSENS			100.0f

void	ft_initialize(void);

int		ft_initial_map_read(const char *src);
void	ft_second_map_read(const char *src, int map_start);
void	ft_checkinput(int argc, char **argv);
void	ft_checkmap(void);
void	ft_printmap(t_map *map);

void	ft_setgame(void);

t_gs	*ft_game(void);

void	ft_free_and_null(void **ptr);
void	ft_clean(void);

void	ft_exit_perror(char *str);
void	ft_exit_error(char *str);
void	ft_exit(void);

// t_player	*init_player(char **map, int w, int h);
void	ft_load_texture(const char *path, mlx_texture_t **texture);
void	ft_load_wall_texture(int index, t_direction dir, mlx_texture_t **texture);


float	ft_height_delta(float distance);
static inline void put_pixel(mlx_image_t *image, u_int32_t x, u_int32_t y, uint32_t color)
{
	if (x < image->width && y < image->height)
		((uint32_t *)image->pixels)[y * image->width + x] = color;
}
void	draw_line_ray(mlx_image_t *image, t_point p0, t_vec3 lookdir, t_map map, int x);
void	draw_wall(mlx_image_t *image, int x);
void	draw_sprite(mlx_image_t *image, t_sprite *sprite);
bool	ft_is_wall(t_vec2 p);
bool	ft_is_door(t_vec2 p);
t_door	*ft_get_door(int x, int y);
void	open_door(int i);
void	fill_background(mlx_image_t *image, uint32_t color);
// void	init_player(void);

void	draw(int32_t width, int32_t height, void *param);
void	draw_ui(void);
void	draw_map(mlx_image_t *image, t_map *map);
void	draw_minimap_bg(void);
void	draw_player(mlx_image_t *image);
void	draw_walls(mlx_image_t *image);
void	draw_sprites(mlx_image_t *image);
void	draw_doors(mlx_image_t *image);
void	draw_square(mlx_image_t *image, int size, t_point pos, uint32_t color);
void	draw_item(mlx_image_t *image, int size, t_point pos, mlx_texture_t *texture);
void	draw_map_square(mlx_image_t *image, t_point pos, uint32_t color);
void	draw_circle(mlx_image_t *image, t_point center, int radius, uint32_t color);
void	draw_line(mlx_image_t *image, t_point start, t_point end, uint32_t color);

uint32_t	ft_get_pixel_color(mlx_texture_t *texture, t_point pixel);
int			ft_get_tex_coord(float x, int texture_width);

void	ft_createhooks(void);
void	ft_key_press_hook(void *param);
void	try_open_doors(t_gs *game);
void	ft_update(void *param);
void	ft_update_hud(void *param);
void	ft_update_minimap(void *param);
void	ft_update_player(void);
void	ft_update_graphics(void);

// math
int			ft_sign(int n);
int			ft_signf(float n);
t_vec2		ft_normalize_vec2(t_vec2 v);
float		ft_angle_between_vec2(t_vec2 a, t_vec2 b);
int			ft_clamp(int value, int min, int max);
float		ft_clampf(float value, float min, float max);

void		print_debug(const char *str);

#endif
