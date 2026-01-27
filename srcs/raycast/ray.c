/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 08:05:18 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/26 09:49:47 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	normalize_angle(float angle)
{
	angle = fmodf(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

static void	cast_ray(t_player *player, float ray_angle, char **map, int id)
{
	t_ray_dir	dir;
	t_ray_calc	calc;

	ray_angle = normalize_angle(ray_angle);
	init_ray_dir(ray_angle, &dir);
	init_horz_intercept(player, ray_angle, &dir, &calc.horz);
	init_vert_intercept(player, ray_angle, &dir, &calc.vert);
	find_horz_hit(&calc.horz, &dir, map, &calc.horz_hit);
	find_vert_hit(&calc.vert, &dir, map, &calc.vert_hit);
	calc.horz_dist = calc_dist(player, &calc.horz_hit);
	calc.vert_dist = calc_dist(player, &calc.vert_hit);
	choose_closest_hit(&calc);
	player->ray[id].ray_angle = ray_angle;
	store_ray_data(player, id, &calc, &dir);
}

void	cast_all_rays(t_player *player, char **map)
{
	const float	fov = PI / 3.0;
	const float	angle_step = fov / NUM_RAYS;
	float		ray_angle;
	int			i;

	ray_angle = player->angle - (fov / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray(player, ray_angle, map, i);
		ray_angle += angle_step;
		i++;
	}
}
