/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 05:58:20 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/25 14:37:17 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int main(void)
{
    t_game game;
    if (!read_file("test.cub", &game.conf))
        return (1); 
    if (!init(&game))
    {
        dispose(&game.conf);
        return (1);
    }
    init_player(&game.player, &game.conf);
    printf("%d %d\n", game.conf.player_x, game.conf.player_y);
    mlx_hook(game.win, KEYPRESS, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, KEYRELEASE, 1L<<1, key_release, &game.player);
    mlx_loop_hook(game.mlx, render, &game);
    mlx_loop(game.mlx);
    return (0);
}