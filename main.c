/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-16 05:58:20 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-16 05:58:20 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool init(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (FALSE);
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
    if (!game->win)
        return (FALSE); // ### TODO: エラー処理
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img)
        return (FALSE); // ### TODO: エラー処理
    return (TRUE);
}

int main(void)
{
    t_game game;
    init(&game);

    mlx_loop(game.mlx);
    return (0);
}