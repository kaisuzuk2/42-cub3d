/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 08:13:01 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/25 16:22:41 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_window(t_game *game)
{
    mlx_loop_end(game->mlx);
    return (0);
}

int key_press(int keycode, t_game *game) \
{
    t_player *player;

    player = &game->player;
    if (keycode == XK_W)
        player->key_up = TRUE;
    if (keycode == XK_S)
        player->key_down = TRUE;
    if (keycode == XK_A)
        player->key_left = TRUE;
    if (keycode == XK_D)
        player->key_right = TRUE;
    if (keycode == XK_LEFT)
        player->left_rotate = TRUE;
    if (keycode == XK_RIGHT)
        player->right_rotate = TRUE;
    if (keycode == XK_ESC)
        mlx_loop_end(game->mlx);
    return (0);
}

int key_release(int keycode, t_game *game)
{
    t_player *player;

    player = &game->player;
    if (keycode == XK_W)
        player->key_up = FALSE;
    if (keycode == XK_S)
        player->key_down = FALSE;
    if (keycode == XK_A)
        player->key_left = FALSE;
    if (keycode == XK_D)
        player->key_right = FALSE;
    if (keycode == XK_LEFT)
        player->left_rotate = FALSE;
    if (keycode == XK_RIGHT)
        player->right_rotate = FALSE;
    return (0);
}