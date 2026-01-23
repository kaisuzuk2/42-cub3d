/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:07:00 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/23 14:08:32 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void init_ray_dir(float ray_angle, t_ray_dir *dir)
{
    dir->is_facing_down = (ray_angle > 0 && ray_angle < PI);
    dir->is_facing_up = !dir->is_facing_down;
    dir->is_facing_right = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
    dir->is_facing_left = !dir->is_facing_right;
}

void init_horz_intercept(t_player *player, float ray_angle, t_ray_dir *dir, t_intercept *horz)
{
    horz->y = floorf(player->y / TILE_SIZE) * TILE_SIZE;
    if (dir->is_facing_down)
        horz->y += TILE_SIZE;
    horz->x = player->x + (horz->y - player->y) / tanf(ray_angle);
    horz->ystep = TILE_SIZE;
    if (dir->is_facing_up)
        horz->ystep *= -1;
    horz->xstep = TILE_SIZE / tanf(ray_angle);
    if (dir->is_facing_left && horz->xstep > 0)
        horz->xstep *= -1;
    if (dir->is_facing_right && horz->xstep < 0)
        horz->xstep *= -1;
}

void init_vert_intercept(t_player *player, float ray_angle, t_ray_dir *dir, t_intercept *vert)
{
    vert->x = floorf(player->x / TILE_SIZE) * TILE_SIZE;
    if (dir->is_facing_right)
        vert->x += TILE_SIZE;
    vert->y = player->y + (vert->x - player->x) * tanf(ray_angle);
    vert->xstep = TILE_SIZE;
    if (dir->is_facing_left)
        vert->xstep *= -1;
    vert->ystep = TILE_SIZE * tanf(ray_angle);
    if (dir->is_facing_up && vert->ystep > 0)
        vert->ystep *= -1;
    if (dir->is_facing_down && vert->ystep < 0)
        vert->ystep *= -1;
}