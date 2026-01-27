/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 08:03:27 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/27 13:40:27 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player, t_config *conf)
{
	player->x = conf->player_x * TILE_SIZE;
	player->y = conf->player_y * TILE_SIZE;
	player->angle = conf->player_init_dir;
	player->key_up = FALSE;
	player->key_down = FALSE;
	player->key_left = FALSE;
	player->key_right = FALSE;
	player->left_rotate = FALSE;
	player->right_rotate = FALSE;
}

static void	rotate_player(t_player *player)
{
	if (player->left_rotate)
		player->angle -= ANGLE_SPEED;
	if (player->right_rotate)
		player->angle += ANGLE_SPEED;
	if (player->angle > TWO_PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = TWO_PI;
}

static void	get_next_player_pos(t_player *player, double *dx, double *dy)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_up)
	{
		*dx += cos_angle * MOVE_SPEED;
		*dy += sin_angle * MOVE_SPEED;
	}
	if (player->key_down)
	{
		*dx -= cos_angle * MOVE_SPEED;
		*dy -= sin_angle * MOVE_SPEED;
	}
	if (player->key_left)
	{
		*dx += sin_angle * MOVE_SPEED;
		*dy -= cos_angle * MOVE_SPEED;
	}
	if (player->key_right)
	{
		*dx -= sin_angle * MOVE_SPEED;
		*dy += cos_angle * MOVE_SPEED;
	}
}

// void	move_player(t_player *player, char **map)
// {
// 	double	dx;
// 	double	dy;

// 	rotate_player(player);
// 	dx = player->x;
// 	dy = player->y;
// 	get_next_player_pos(player, &dx, &dy);
// 	if (!map_has_wall_at(dx, dy, map))
// 	{
// 		player->x = dx;
// 		player->y = dy;
// 	}
// }


void	move_player(t_player *player, char **map)
{
	double	dx;
	double	dy;
	
	rotate_player(player);
	dx = player->x;
	dy = player->y;
	get_next_player_pos(player, &dx, &dy);
	if (!map_has_wall_at(dx, player->y, map))
		player->x = dx;
	if (!map_has_wall_at(player->x, dy, map))
		player->y = dy;
}
