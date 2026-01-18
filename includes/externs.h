/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-18 05:07:28 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-18 05:07:28 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNS_H
# define EXTERNS_H

#include "cub3d.h"

// init.c
t_bool init(t_game *game);

// input.c
int key_press(int keycode, t_player *player);
int key_release(int keycode, t_player *player);

// draw.c
void put_pixel(t_img *img, int x, int y, int color);
void draw_square(int x, int y, int size, int color, t_img *img);
void clear_image(t_img *img);
void draw_wall_split(t_img *img ,int x, int top, int bottom, int color);

// map.c
char **get_map(void);
t_bool map_has_wall_at(double x, double y, char **map);

// tex.c
unsigned int get_texel(t_tex *tex, int x, int y);
t_tex *select_wall_tex(t_game *game, t_ray *ray);
t_bool load_texture(t_game *game, t_tex *tex, char *path);

// player.c
void init_player(t_player *player);
void move_player(t_player *player, char **map);

// ray.c
void cast_all_rays(t_player *player, char **map);

// render.c
int render(t_game *game);


#endif