/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:23:04 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/26 10:25:18 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// fisheye
// cos = fromt / dist
float	calc_perp_dist(t_ray *ray, float player_angle)
{
	float	res;

	res = ray->distance * cosf(ray->ray_angle - player_angle);
	if (res < 0.0001f)
		res = 0.0001f;
	return (res);
}

void	calc_wall(float perp_dist, int *top, int *bottom)
{
	const float	fov = PI / 3.0f;
	const float	dist_proj = (WIDTH / 2.0f) / tanf(fov / 2.0f);
	float		proj_wall_h;
	int			wall_h;

	proj_wall_h = (TILE_SIZE / perp_dist) * dist_proj;
	wall_h = (int)proj_wall_h;
	*top = (HEIGHT / 2) - (wall_h / 2);
	*bottom = (HEIGHT / 2) + (wall_h / 2);
	if (*top < 0)
		*top = 0;
	if (*bottom >= HEIGHT)
		*bottom = HEIGHT - 1;
}
