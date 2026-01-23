/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:09:31 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/23 14:09:58 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static t_bool is_hit_horz_wall(t_intercept *horz, t_ray_dir *dir, char **map, t_hit *hit)
{
    float x_check;
    float y_check;

    x_check = horz->x;
    y_check = horz->y;
    if (dir->is_facing_up)
        y_check -= 1;
    if (map_has_wall_at(x_check, y_check, map))
    {
        hit->x = horz->x;
        hit->y = horz->y;
        return (TRUE);
    }    
    return (FALSE);
}

static t_bool is_hit_vert_wall(t_intercept *vert, t_ray_dir *dir, char **map, t_hit *hit)
{
    float x_check;
    float y_check;

    x_check = vert->x;
    y_check = vert->y;
    if (dir->is_facing_left)
        x_check -= 1;
    if (map_has_wall_at(x_check, y_check, map))
    {
        hit->x = vert->x;
        hit->y = vert->y;
        return (TRUE);
    }
    return (FALSE);
}

void find_horz_hit(t_intercept *horz, t_ray_dir *dir, char **map, t_hit *hit)
{
    hit->is_found = FALSE;
    hit->x = 0;
    hit->y = 0;
    while (1)
    {
        if (is_hit_horz_wall(horz, dir, map, hit))
        {
            hit->is_found = TRUE;
            break;
        }
        horz->x += horz->xstep;
        horz->y += horz->ystep;
    }
}

void find_vert_hit(t_intercept *vert, t_ray_dir *dir, char **map, t_hit *hit)
{
    hit->is_found = FALSE;
    hit->x = 0;
    hit->y = 0;
    while (1)
    {
        if (is_hit_vert_wall(vert, dir, map, hit))
        {
            hit->is_found = TRUE;
            break;
        }
        vert->x += vert->xstep;
        vert->y += vert->ystep;
    }
}
