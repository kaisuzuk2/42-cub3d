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

typedef struct s_img {
   void *img_ptr;
   char *addr;
   int bpp;
   int size_line;
   int endian;
} t_img;

typedef struct s_player {
    float x;
    float y;
    float width;
    float height;
    int turn_direction;
    int walk_direction; 
    float rotation_angle;
    float walk_speed;
    float turn_spead;
} t_player;


typedef struct s_game {
    void *mlx;
    void *win;
    t_img img;
    t_player player;
} t_game;

#endif