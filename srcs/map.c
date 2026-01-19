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

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "1000000000000011111111111";
    map[2] = "1000000000000000000000001";
    map[3] = "1000001000000000000000001";
    map[4] = "1000000000000000000000001";
    map[5] = "1000000100000011111111111";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

t_bool map_has_wall_at(double x, double y, char **map) 
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return (TRUE);
    int row;
    row = 0;
    while (map[row])
        row++;
    int col;
    col = 0;
    while (map[0][col])
        col++;
    if ((int)(y / TILE_SIZE) >= row)
        return (TRUE);
    if ((int)(x / TILE_SIZE) >= col)
        return (TRUE);
    return (map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '0');
}