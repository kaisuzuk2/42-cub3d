/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-18 07:54:42 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-18 07:54:42 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool init(t_game *game, t_config *conf)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (FALSE);
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
    if (!game->win)
        return (FALSE); // ### TODO: エラー処理
    game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img.img_ptr)
        return (FALSE); // ### TODO: エラー処理
    game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.size_line, &game->img.endian);
    game->map = conf->map;
    if (!load_texture(game, &game->tex_n, "textures/north.xpm"))
        return (FALSE); // ### TODO: エラー処理
    if (!load_texture(game, &game->tex_s, "textures/south.xpm"))
        return (FALSE); // ### TODO: エラー処理
    if (!load_texture(game, &game->tex_e, "textures/east.xpm"))
        return (FALSE); // ### TODO: エラー処理
    if (!load_texture(game, &game->tex_w, "textures/west.xpm"))
        return (FALSE); // ### TODO: エラー処理
    return (TRUE);
}
