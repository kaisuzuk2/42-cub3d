/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:11:51 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/26 09:47:48 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calc_dist(t_player *player, t_hit *hit)
{
	float	dx;
	float	dy;

	if (!hit->is_found)
		return (INFINITY);
	dx = hit->x - player->x;
	dy = hit->y - player->y;
	return (sqrt(dx * dx + dy * dy));
}

void	choose_closest_hit(t_ray_calc *calc)
{
	if (calc->horz_dist < calc->vert_dist)
	{
		calc->final.x = calc->horz_hit.x;
		calc->final.y = calc->horz_hit.y;
		calc->final.dist = calc->horz_dist;
		calc->final.is_vertical = FALSE;
	}
	else
	{
		calc->final.x = calc->vert_hit.x;
		calc->final.y = calc->vert_hit.y;
		calc->final.dist = calc->vert_dist;
		calc->final.is_vertical = TRUE;
	}
}

void	store_ray_data(t_player *player, int id, t_ray_calc *calc,
		t_ray_dir *dir)
{
	player->ray[id].distance = calc->final.dist;
	player->ray[id].wall_hit_x = calc->final.x;
	player->ray[id].wall_hit_y = calc->final.y;
	player->ray[id].was_hit_vertical = calc->final.is_vertical;
	player->ray[id].is_facing_up = dir->is_facing_up;
	player->ray[id].is_facing_down = dir->is_facing_down;
	player->ray[id].is_facing_left = dir->is_facing_left;
	player->ray[id].is_facing_right = dir->is_facing_right;
}
