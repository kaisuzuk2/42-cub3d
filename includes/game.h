/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-16 06:03:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-16 06:03:57 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define WIDTH 1280
# define HEIGHT 720

typedef int t_bool;
#define TRUE 1
#define FALSE 0

#define NUM_RAYS WIDTH

# define TEX_LABEL 3
# define COLOR_LABEL 2
# define RGB_COUNT 3

typedef struct s_config 
{
    char *path_n;
    char *path_s;
    char *path_e;
    char *path_w;

    int ceil_color;
    int floor_color;

    char **map;
    char player_dir;
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