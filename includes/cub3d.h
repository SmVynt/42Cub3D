/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:05:05 by psmolin           #+#    #+#             */
/*   Updated: 2025/11/14 11:24:28 by psmolin          ###   ########.fr       */
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
# include "structs.h"
# include "ft_mat4.h"

# define DEBUG_MODE				false

# define MIN_WIDTH				128
# define MIN_HEIGHT				72
# define WIDTH					1280
# define HEIGHT					720

# define COLOR_WHITE			0xFFFFFFFF
# define COLOR_BLACK			0xFF000000
# define COLOR_RED				0xFF0000FF
# define COLOR_GREEN			0xFF00FF00
# define COLOR_BLUE				0xFFFF0000
# define COLOR_YELLOW			0xFF00FFFF
# define COLOR_GREY				0xFF808080
# define COLOR_RED_TRANSP		0xFF00001A

# define COLOR_R				"\033[31m"
# define COLOR_G				"\033[32m"
# define COLOR_Y				"\033[33m"
# define COLOR_B				"\033[34m"
# define COLOR_M				"\033[35m"
# define COLOR_C				"\033[36m"
# define COLOR_W				"\033[37m"
# define COLOR_BOLD				"\033[1m"
# define COLOR_X				"\033[0m"

# define MAP_ALLOWED_CHARS		"0123456789:#NSEW _+.KbasdDfmX"
# define MAP_WALL_CHARS			"123456789:"
# define MAP_PLAYER_CHARS		"NSEW"
# define MAP_MANDATORY_CHARS	"01 NSEW"

# define MAP_SCALE				10
# ifndef M_PI
#  define M_PI					3.14159265358979323846
# endif
# define HALF_PI				1.57079632679489661923
# define FOV_RAD				1.04719755119659774615
# define PIXEL_SIZE				4
# define UI_PIXEL_SIZE			1
# define STANDARD_SPRITE_SIZE	64
# define JUMP_HEIGHT			1.0
# define JUMP_IMPULSE			3.2f
# define GRAVITY				9.8f
# define TILE_BORDER			0.1
# define TARGET_FPS				60.0
# define MAX_DT					0.05
# define DOOR_OPEN_TIME			1.0
# define INTERACT_DIST			2.0
# define INTERACT_ANGLE			1.04719755119659774615
# define PLAYERSPEED			6.0
# define ROTATIONSPEED			2.0
# define MOUSE_XSENS			2.0
# define MOUSE_YSENS			100.0
# define RAYCAST_MAX_ITER		100

// initialization
void		ft_assign_textures(void);
void		ft_assign_colors(void);
void		ft_initialize(void);
int			ft_initial_map_read(const char *src);
void		ft_second_map_read(const char *src, int map_start);
void		ft_checkinput(int argc, char **argv);
void		ft_checkmap(void);
void		ft_printmap(t_map *map);
void		ft_init_prefabs(void);
void		ft_init_prefabs_items(t_gs *game);
void		ft_init_prefabs_chars(t_gs *game);
void		ft_init_prefabs_interacts(t_gs *game);
void		ft_init_null_textures(void);

void		ft_setgame(void);

t_gs		*ft_game(void);

void		ft_exit_perror(char *str);
void		ft_exit_error(char *str);
void		ft_exit(void);

void		ft_load_texture(const char *path, mlx_texture_t **texture);
void		ft_load_anim_texture(const char *path, mlx_texture_t **frames,
				int n_frames);
void		ft_load_texture_from_atlas(int row, int col,
				mlx_texture_t **texture, mlx_texture_t *atlas);

static inline void	put_pixel(mlx_image_t *image, uint32_t x, uint32_t y,
				uint32_t color)
{
	if (x < image->width && y < image->height)
		((uint32_t *)image->pixels)[y * image->width + x] = color;
}
void		draw_wall(mlx_image_t *image, int x);
void		draw_sprite(mlx_image_t *image, t_sprite *sprite);
void		ft_calculate_sprite(mlx_image_t *image, t_sprite *sprite);

t_door		*ft_get_door(int x, int y);
void		interact(t_gs *game);
bool		can_interact(t_door wall, int *side);
void		print_interact_msg(t_gs *game);
void		open_door(int i);

// render helper functions
bool		allocate_depth_buffer(t_gs *game, int32_t width);
void		setup_minimap_positions(t_gs *game, int32_t width, int32_t height);
void		ft_fill_split_bg(mlx_image_t *bg);
void		fill_background(mlx_image_t *image, uint32_t color);

void		draw(int32_t width, int32_t height, void *param);
void		draw_ui(void);
void		draw_ui_img(mlx_image_t *img, mlx_texture_t *tex);
void		draw_map(void);
void		draw_chars_on_minimap(mlx_image_t *img, double zoom,
				t_point img_center);
void		draw_items_on_minimap(mlx_image_t *img, double zoom,
				t_point img_center);

void		draw_walls(mlx_image_t *image);
void		draw_cubemap(mlx_image_t *image, t_rayrender *ray,
				t_point screen_coords);
void		draw_floor_part(t_rayrender ray, int x, int wall_end);
void		draw_ceil_part(t_rayrender ray, int x, double wall_start);
void		draw_wall_part(t_rayrender ray, int x, double wall_start);
void		draw_sprites(mlx_image_t *image);
void		draw_square(mlx_image_t *image, int size, t_point pos,
				uint32_t color);
void		draw_ui_item(mlx_image_t *image, int size, t_point pos,
				mlx_texture_t *texture);
void		draw_circle(mlx_image_t *image, t_point center, int radius,
				uint32_t color);
t_vec2		get_ray_end(t_rayrender *ray);
t_vec2		get_next_wall_intersection(t_vec2 pos, t_vec2 dir, t_point *tile,
				int *side);
bool		process_wall_hit(t_rayrender *ray, t_vec2 *curr, t_point tile,
				int *side);

void		pick_up(t_item *item);

uint32_t	ft_get_pixel_color(mlx_texture_t *texture, t_point pixel);
int			ft_get_tex_coord(double x, int texture_width);

void		ft_createhooks(void);
void		ft_key_press_hook(void *param);

// initialization
void		ft_init_walls_textures(void);
void		ft_init_floor_textures(void);
void		ft_init_ceiling_textures(void);
void		ft_init_end_screen_textures(void);
void		ft_init_ui_textures(void);
void		ft_set_doors(void);
void		ft_set_items(void);
void		ft_set_chars(void);
void		ft_init_sprites(void);

// update
void		ft_update_dt(void);
void		ft_update(void *param);
void		ft_update_minimap(void);
void		ft_update_hp_bar(void);
void		ft_update_chars(void);
void		ft_update_player(void);
void		ft_update_graphics(void);
void		clear_image(mlx_image_t *image);
void		shaky_shaky(void);

// ai
void		ft_ai_alien(t_char *ch);

// tile checks
bool		ft_is_special_wall(t_vec2 p, const char *wall_type);
bool		ft_is_wall(t_vec2 p);
bool		ft_is_lava(t_vec2 p);
bool		ft_is_pod(t_vec2 p);
bool		ft_is_door(t_vec2 p);

void		show_end_screen(void);
bool		ft_player_try_damage(double damage);
bool		ft_player_try_heal(double heal);

// math
int			ft_sign(int n);
int			ft_signd(double n);
t_vec2		ft_normalize_vec2(t_vec2 v);
double		ft_angle_between_vec2(t_vec2 a, t_vec2 b);
int			ft_clamp(int value, int min, int max);
double		ft_clampf(double value, double min, double max);
double		ft_lerpf(double a, double b, double t);
t_vec2		ft_lerpvec2(t_vec2 a, t_vec2 b, double t);
double		rand_in_range(double min, double max);

void		print_debug(const char *str);

// cleaning
void		ft_free_and_null(void **ptr);
void		ft_clean(void);
void		ft_free_string(char **ptr);
void		ft_free_mlx(void);
void		ft_freemap(void);
void		ft_free_texture(mlx_texture_t **texture);
void		ft_free_image(mlx_image_t **image);
void		ft_free_render(void);
void		ft_free_mlx_envirtex(t_gs *game);
void		ft_free_mlx_prefabs_chars(t_gs *game);
void		ft_free_mlx_prefabs_items(t_gs *game);
void		ft_free_mlx_prefabs_specials(t_gs *game);

#endif
