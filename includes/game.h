/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 06:03:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/25 15:43:05 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define WIDTH 1280
# define HEIGHT 720

# define CUB_FILE_EXT ".cub"

# define WEST_TEX_LAB "WE "
# define EAST_TEX_LAB "EA "
# define SOUTH_TEX_LAB "SO "
# define NORTH_TEX_LAB "NO "
# define FLOOR_TEX_LAB "F "
# define CEIL_TEX_LAB "C "

# define TEX_LAB_LEN 3
# define COLOR_LAB_LEN 2
# define RGB_COUNT 3

# define ANGLE_SPEED 0.03f
# define MOVE_SPEED 1

typedef int t_bool;
#define TRUE 1
#define FALSE 0

typedef t_bool (*t_handler)(char **dst, char *val);

typedef struct s_rule {
    const char *label;
    char **dst;
    t_handler handler;
} t_rule;


#define NUM_RAYS WIDTH


typedef struct s_ray_dir {
    t_bool is_facing_up;
    t_bool is_facing_down;
    t_bool is_facing_left;
    t_bool is_facing_right;
} t_ray_dir;

typedef struct s_intercept {
    float x;
    float y;
    float xstep;
    float ystep;
} t_intercept;

typedef struct s_hit {
    t_bool is_found;
    float x;
    float y;
} t_hit;

typedef struct s_final_hit {
    float x;
    float y;
    float dist;
    t_bool is_vertical;
} t_final_hit; 

typedef struct s_ray_calc
{   
    t_intercept horz;
    t_intercept vert;
    t_hit horz_hit;
    t_hit vert_hit;
    t_final_hit final;
    float horz_dist;
    float vert_dist;
} t_ray_calc;

typedef struct s_config 
{
    char *path_n;
    char *path_s;
    char *path_e;
    char *path_w;

    int ceil_color;
    int floor_color;

    char **map;
    char player_dir_char;
    float player_init_dir;
    int player_x;
    int player_y;
} t_config;

typedef struct s_tex {
    void *img_ptr;
    char *addr;
    int w;
    int h;
    int bpp;
    int size_line;
    int endian;
} t_tex;

typedef struct s_img {
   void *img_ptr;
   char *addr;
   int bpp;
   int size_line;
   int endian;
} t_img;


typedef struct s_ray {
    float ray_angle;
    float wall_hit_x;
    float wall_hit_y;
    float distance;
    int was_hit_vertical;
    int is_facing_up;
    int is_facing_down;
    int is_facing_left;
    int is_facing_right;
    int wall_hit_content;
} t_ray;


typedef struct s_player {
    float x;
    float y;
    float angle;
    t_bool key_up;
    t_bool key_down;
    t_bool key_left;
    t_bool key_right;
    t_bool left_rotate;
    t_bool right_rotate;
    t_ray ray[WIDTH];
} t_player;

typedef struct s_game {
    void *mlx;
    void *win;
    t_img img;
    t_player player;   
    t_config conf;

    t_tex tex_n;
    t_tex tex_s;
    t_tex tex_e;
    t_tex tex_w;
} t_game;

#endif