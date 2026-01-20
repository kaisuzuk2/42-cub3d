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


char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "          111111111111111";
    map[1] = "          100000000000001";
    map[2] =           "100000000000001";
    map[3] = "          100011111111111";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

// t_bool map_has_wall_at(double x, double y, char **map) 
// {
//     int row;
//     int col;

//     // if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
//     //     return (TRUE);
//     if (x < 0 || y < 0)
//         return (TRUE);
//     row = 0;
//     while (map[row])
//         row++;
//     if ((int)(y / TILE_SIZE) >= row)
//         return (TRUE);
//     col = 0;
//     while (map[(int)(y / TILE_SIZE)][col])
//         col++;
//     if ((int)(x / TILE_SIZE) >= col)
//         return (TRUE);
//     return (map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '0');
// }

t_bool map_has_wall_at(double x, double y, char **map)
{
    int map_x;
    int map_y;
    int h;

    if (!map)
        return (TRUE);

    // ワールド座標が負なら即「外」
    if (x < 0 || y < 0)
        return (TRUE);

    map_x = (int)(x / TILE_SIZE);
    map_y = (int)(y / TILE_SIZE);

    // タイル座標が負なら即「外」
    if (map_x < 0 || map_y < 0)
        return (TRUE);

    // 高さを数えて、map_y が範囲外なら「外」
    h = 0;
    while (map[h])
        h++;
    if (map_y >= h)
        return (TRUE);

    // 幅（行長）を見て、map_x が範囲外なら「外」
    // ※行長がバラバラでも安全
    if (map_x >= (int)ft_strlen(map[map_y]))
        return (TRUE);

    // 空白は「外(=壁扱い)」に統一するのが安定
    if (map[map_y][map_x] == ' ')
        return (TRUE);

    return (map[map_y][map_x] == '1');
}
