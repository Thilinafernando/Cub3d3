/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:23:13 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/24 21:55:05 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include "libft/libft.h"
# include "libprintf/ft_printf.h"
# include "get_next_line/get_next_line.h"

# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>

# define WINDOW_WIDTH 900
# define WINDOW_HEIGHT 800
# define TEXTURE_SIZE 515
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
#define MAX_DOORS 128
#define MINIMAP_SCALE 10
#define MINIMAP_RADIUS_TILES 5
#define MINIMAP_DIAMETER (MINIMAP_RADIUS_TILES * 2 * MINIMAP_SCALE)
#define MINIMAP_RADIUS_PIXELS (MINIMAP_RADIUS_TILES * MINIMAP_SCALE)
#define MINIMAP_OFFSET_X 10
#define MINIMAP_OFFSET_Y 675

typedef struct s_minimap
{
    int     dx;
    int     dy;
    int     px;
    int     py;
    int     point_x;
    int     point_y;
    int     perp_x;
    int     perp_y;
    int     full;
    int	w;
	int	h;
} t_minimap;

typedef struct s_draw_params
{
	int	tex_num;
	int	tex_x;
	int	x;
}	t_draw_params;

typedef struct s_wall_vars
{
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;
}	t_wall_vars;
// this for the door is open or not ok thilina
typedef struct s_door
{
	int x;
	int y;
	int is_open;  // 0 = closed, 1 = open
} t_door;


typedef struct s_info
{
	char	**file;
	char	**map;
	int		count;
	int		max;
	char	**tmp;
	int		player_x;
	int		player_y;
	int		flood_flag;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	int		rgb_f;
	int		rgb_c;
}	t_info;

typedef struct s_player
{
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_ray
{
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int step_x;
    int step_y;
    int hit;
    int side;
    int line_height;
    int draw_start;
    int draw_end;
} t_ray;

typedef struct s_texture
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    int width;
    int height;
} t_texture;

typedef struct s_game
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    t_info *info;
    t_player player;
    t_texture textures[5]; // NO, SO, WE, EA
    t_texture weapon_texture;
    t_texture weapon_fire_textures[2];
    int keys[256];
    int mouse_x;           // Add this
    int mouse_y;           // Add this
    int prev_mouse_x;      // Add this
    int mouse_enabled;     // Add this
    t_door doors[MAX_DOORS];// bonus
    int door_count;// bonus
    int is_shooting;// for bonus
    int shoot_timer; // frames to display the shooting sprite //bonus
    int current_fire_frame; // 0 or 1
    int	px;
    int	py;
	int	pixel_dx;
	int	pixel_dy;
    t_minimap *minimap;
} t_game;

//parsing functions (your friend's code)
bool	xmp_extention_check(char *str);
bool	extention_check(char *str);
int		paths_conditions(t_info *info, int i, int j, char *str);
int		fill_file(char *map, t_info *info);
int		fill_map(t_info *info);
int		validate_map(t_info *info);
int		paths_check(t_info *info, int i, char *str);
int		check_spaces(t_info *info);
int		paths(t_info *info);
int		count_lines(char *map);
bool	map_only(char *str);
char	*ft_mapdup(const char *s, t_info *info);
char	*x_fill(t_info *info);
int		fill_tmp(t_info *info);
void	print_matrix(char **matrix);
int		find_player_pos(char **matrix, t_info *info);
bool	verify_char(char c);
void	flood_fill(int x, int y, t_info *info);
int		check_playable(t_info *info);
int		check_characters(t_info *info);
char	*ft_mydup(const char *s);
void	init_struct(t_info *info);
int		rgb_convertion(t_info *info, char *str, int i, int j);
int		save_path(char *str, t_info *info, int i, int j);
void	free_all(t_info *info);

//rendering functions (your code)
void	init_player(t_game *game);
int		load_texture(t_game *game, t_texture *texture, char *path);
int		load_textures(t_game *game);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
int		get_texture_color(t_texture *texture, int x, int y);
void	perform_dda(t_game *game, t_ray *ray);
void	calculate_ray(t_game *game, t_ray *ray, int x);
void	draw_wall(t_game *game, t_ray *ray, int x);
void	draw_floor_ceiling(t_game *game, t_ray *ray, int x);
void	raycast(t_game *game);
void draw_weapon(t_game *game);
void init_doors(t_game *game);
int is_door_open(t_game *game, int x, int y);
int is_wall_or_closed_door(t_game *game, double x, double y);
//game controls functions
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	move_player(t_game *game);
int		game_loop(t_game *game);
int		close_game(t_game *game);
int		init_mlx(t_game *game);
void    free_game_resources(t_game *game);
void    free_textures(t_game *game);
void    free_mat(char **matrix);
void    try_open_close_door(t_game *game); //bonus
void    try_toggle_door(t_game *game);
//control mouse.c
int mouse_release(int button, int x, int y, t_game *game);
int mouse_press(int button, int x, int y, t_game *game);
int mouse_move(int x, int y, t_game *game);
//minimap.c
void	set_zero_mini(t_minimap *minimap);
void	draw_player_body(t_game *game, int px, int py);
void	process_draw_arrow(t_game *game, int px, int py, int dist);
void	draw_player_arrow(t_game *game, int px, int py);
void	draw_tile_if_in_circle(t_game *game, int tile_x, int tile_y, int color);
int	    get_tile_color(char tile);
void	draw_moving_minimap_tiles(t_game *game);
void	draw_accurate_player_dot(t_game *game);
void	draw_minimap_background_circle(t_game *game);
void	draw_minimap(t_game *game);

int	key_release(int keycode, t_game *game);
int game_loop(t_game *game);
int	close_game(t_game *game);
int	get_texture_number(t_ray *ray);
void	init_wall_vars(t_wall_vars *vars, t_game *game, t_ray *ray, int tex_num);
int	calculate_tex_x(t_game *game, t_ray *ray, double wall_x, int tex_num);
double	calculate_wall_x(t_game *game, t_ray *ray);
void	draw_wall(t_game *game, t_ray *ray, int x);
void	move_forward_bonus(t_game *game);
void	move_backward_bonus(t_game *game);
void	draw_texture_column(t_game *game, t_ray *ray, t_draw_params *params);
void	get_door_texture(t_game *game, t_ray *ray, int *tex_num, double *wall_x);
void	get_regular_wall_texture(t_game *game, t_ray *ray, int *tex_num, double *wall_x);
#endif
