/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 05:08:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/27 14:18:06 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_texel(const t_tex *tex, int x, int y)
{
	char	*dst;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= tex->w)
		x = tex->w - 1;
	if (y >= tex->h)
		y = tex->h - 1;
	dst = tex->addr + y * tex->size_line + x * (tex->bpp / 8);
	return (*(unsigned int *)dst);
}

int	get_tex_x(t_ray *ray, const t_tex *tex)
{
	float	hit;
	int		tex_x;

	if (ray->was_hit_vertical)
		hit = ray->wall_hit_y;
	else
		hit = ray->wall_hit_x;
	tex_x = (int)fmodf(hit, TILE_SIZE);
	tex_x = (int)((float)tex_x * tex->w / TILE_SIZE);
	if (ray->was_hit_vertical && cos(ray->ray_angle) < 0)
		tex_x = tex->w - tex_x - 1;
	if (!ray->was_hit_vertical && sin(ray->ray_angle) > 0)
		tex_x = tex->w - tex_x - 1;
	return (tex_x);
}

t_tex	*select_wall_tex(t_game *game, t_ray *ray)
{
	if (ray->was_hit_vertical)
	{
		if (ray->is_facing_right)
			return (&game->tex_w);
		else
			return (&game->tex_e);
	}
	else
	{
		if (ray->is_facing_down)
			return (&game->tex_n);
		else
			return (&game->tex_s);
	}
}

t_bool	load_texture(t_game *game, t_tex *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx, path, &tex->w, &tex->h);
	if (!tex->img_ptr)
		return (FALSE);
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->size_line,
			&tex->endian);
	if (!tex->addr)
		return (FALSE);
	return (TRUE);
}
