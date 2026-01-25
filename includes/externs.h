/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 05:07:28 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/25 14:36:53 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNS_H
# define EXTERNS_H

#include "cub3d.h"

// parse.c
t_bool read_file(char *file_name, t_config *conf);

//parse_utils.c
void init_config(t_config *conf);
void free_split(char **ptr);

// parse_config.c
t_bool read_config(int fd, t_config *conf);

//parse_map.c
t_bool read_map(int fd, t_config *conf);

//parse_valid_map.c
t_bool is_map_closed(t_config *conf);
t_bool setup_player_from_map(t_config *conf);

// init.c
t_bool init(t_game *game);

// input.c
int key_press(int keycode, t_player *player);
int key_release(int keycode, t_player *player);

// draw.c
void put_pixel(t_img *img, int x, int y, int color);
void draw_square(int x, int y, int size, int color, t_img *img);
void clear_image(t_img *img);

// map.c
char **get_map(void);
t_bool map_has_wall_at(double x, double y, char **map);

// tex.c
unsigned int get_texel(t_tex *tex, int x, int y);
t_tex *select_wall_tex(t_game *game, t_ray *ray);
t_bool load_texture(t_game *game, t_tex *tex, char *path);

// player.c
void init_player(t_player *player, t_config *conf);
void move_player(t_player *player, char **map);

// ray.c
void cast_all_rays(t_player *player, char **map);

// ray_init.c
void init_ray_dir(float ray_angle, t_ray_dir *dir);
void init_horz_intercept(t_player *player, float ray_angle, t_ray_dir *dir, t_intercept *horz);
void init_vert_intercept(t_player *player, float ray_angle, t_ray_dir *dir, t_intercept *vert);

// ray_dda.c
void find_vert_hit(t_intercept *vert, t_ray_dir *dir, char **map, t_hit *hit);
void find_horz_hit(t_intercept *horz, t_ray_dir *dir, char **map, t_hit *hit);

// ray_utils.c
float calc_dist(t_player *player, t_hit *hit);
void choose_closest_hit(t_ray_calc *calc);
void store_ray_data(t_player *player, int id, t_ray_calc *calc, t_ray_dir *dir);

// render.c
int render(t_game *game);

// error.c
void print_error(char *str);
void print_sys_error(char *func);
void print_error_detail(char *str, char *near);

// dispose.c
void dispose(t_config *conf);

#endif