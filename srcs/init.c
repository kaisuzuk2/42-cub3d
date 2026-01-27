/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 07:54:42 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/27 16:01:55 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	load_texture(t_game *game, t_tex *tex, char *path)
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

t_bool	init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error(MLX_LABEL, "failed to initialize mlx."), FALSE);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	if (!game->win)
		return (print_error(MLX_LABEL, "failed to create window."), FALSE);
	game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img_ptr)
		return (print_error(MLX_LABEL, "failed to get image data."), FALSE);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.size_line, &game->img.endian);
	if (!load_texture(game, &game->tex_n, game->conf.path_n)
		|| !load_texture(game, &game->tex_s, game->conf.path_s)
		|| !load_texture(game, &game->tex_e, game->conf.path_e)
		|| !load_texture(game, &game->tex_w, game->conf.path_w))
		return (print_error(MLX_LABEL, "failed to load texture."), FALSE);
	return (TRUE);
}
