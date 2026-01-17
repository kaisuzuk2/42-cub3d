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
    float angle;
    t_bool key_up;
    t_bool key_down;
    t_bool key_left;
    t_bool key_right;
    t_bool left_rotate;
    t_bool right_rotate;

} t_player;


typedef struct s_game {
    void *mlx;
    void *win;
    t_img img;
    t_player player;   
    char **map;
} t_game;

#endif