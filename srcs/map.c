/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-18 08:10:41 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-18 08:10:41 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// char **get_map(void)
// {
//     char **map = malloc(sizeof(char *) * 11);
//     map[0] = "111111111111111";
//     map[1] = "100000000000001";
//     map[2] = "100000000000001";
//     map[3] = "100000100000001";
//     map[4] = "100000000000001";
//     map[5] = "100000010000001";
//     map[6] = "100001000000001";
//     map[7] = "100000000000001";
//     map[8] = "100000000000001";
//     map[9] = "111111111111111";
//     map[10] = NULL;
//     return (map);
// }

t_bool map_has_wall_at(double x, double y, char **map)
{
    int map_x;
    int map_y;
    int h;

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
