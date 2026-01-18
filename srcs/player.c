/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-18 08:03:27 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-18 08:03:27 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_player *player) 
{
    player->x = WIDTH / 2;
    player->y = HEIGHT / 2;
    player->angle = PI / 2;
    player->key_up = FALSE;
    player->key_down = FALSE;
    player->key_left = FALSE;
    player->key_right = FALSE;
    player->left_rotate = FALSE;
    player->right_rotate = FALSE;
}


void move_player(t_player *player, char **map)
{
    const int speed = 1;
    const float angle_speed = 0.03;
    float cos_angle;
    float sin_angle;
    double dx;
    double dy;

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    if (player->angle > TWO_PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = TWO_PI;

    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);

    dx = player->x;
    dy = player->y;

    if (player->key_up)
    {
        dx += cos_angle * speed;
        dy += sin_angle * speed;
    }
    if (player->key_down)
    {
        dx -= cos_angle * speed;
        dy -= sin_angle * speed;
    }
    if (player->key_left)
    {
        dx += sin_angle * speed;
        dy -= cos_angle * speed;
    }
    if (player->key_right)
    {
        dx -= sin_angle * speed;
        dy += cos_angle * speed;
    }
    if (!map_has_wall_at(dx, dy, map))
    {
        player->x = dx;
        player->y = dy;
    }
}