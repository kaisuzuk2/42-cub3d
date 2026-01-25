/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:32:02 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/25 14:55:31 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void dispose_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void dispose_conf(t_config *conf) 
{
	free(conf->path_n);
	free(conf->path_s);
	free(conf->path_e);
	free(conf->path_w);
	dispose_map(conf->map);
}

void dispose_game(t_game *game)
{	
	if (game->tex_w.img_ptr)
		mlx_destroy_image(game->mlx, game->tex_w.img_ptr);
	if (game->tex_e.img_ptr)
		mlx_destroy_image(game->mlx, game->tex_e.img_ptr);
	if (game->tex_s.img_ptr)
		mlx_destroy_image(game->mlx, game->tex_s.img_ptr);
	if (game->tex_n.img_ptr)
		mlx_destroy_image(game->mlx, game->tex_n.img_ptr);
	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx, game->img.img_ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}