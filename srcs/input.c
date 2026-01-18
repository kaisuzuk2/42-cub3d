/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-18 08:13:01 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-18 08:13:01 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int key_press(int keycode, t_player *player) \
{
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
    return (0);
}

int key_release(int keycode, t_player *player)
{
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