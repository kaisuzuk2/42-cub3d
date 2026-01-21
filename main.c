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
#include <stdio.h>

int main(void)
{
    t_game game;
    if (!read_file("test.cub", &game.conf))
        return (1); // ### TODO: エラー処理
    printf("%s\n", game.conf.path_n);
    if (!init(&game))
        return (1); // ### TODO: エラー処理
    init_player(&game.player, &game.conf);
    mlx_hook(game.win, KEYPRESS, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, KEYRELEASE, 1L<<1, key_release, &game.player);
    mlx_loop_hook(game.mlx, render, &game);
    mlx_loop(game.mlx);
    return (0);
}