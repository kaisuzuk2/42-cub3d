/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 08:10:41 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/26 09:37:27 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	map_has_wall_at(double x, double y, char **map)
{
	int	map_x;
	int	map_y;
	int	h;

	if (!map)
		return (TRUE);
	if (x < 0 || y < 0)
		return (TRUE);
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0)
		return (TRUE);
	h = 0;
	while (map[h])
		h++;
	if (map_y >= h)
		return (TRUE);
	if (map_x >= (int)ft_strlen(map[map_y]))
		return (TRUE);
	if (map[map_y][map_x] == ' ')
		return (TRUE);
	return (map[map_y][map_x] == '1');
}
