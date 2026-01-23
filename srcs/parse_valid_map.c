/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:23:15 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/23 15:39:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool is_player_char(const char c)
{
    return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static t_bool is_valid_map_char(const char c)
{
    return (is_player_char(c) || c == '1' || c == '0' || c == ' ');
}

static double dir_to_angle(const char c)
{
    if (c == 'E')
        return (0.0);
    if (c == 'S')
        return (PI / 2);
    if (c == 'W')
        return (PI);
    if (c == 'N')
        return (3 * PI / 2);
    return (0.0);
}


t_bool detect_player(t_config *conf)
{
    int y;
    int x;
    
    y = 0;
    while (conf->map && conf->map[y])
    {
        x = 0;
        while (conf->map[y][x])
        {
            if (!is_valid_map_char(conf->map[y][x]))
                return (FALSE); // ### TODO: エラー処理
            if (is_player_char(conf->map[y][x]))
            {
                if (conf->player_dir_char != 0)
                    return (FALSE); // ### TODO: エラー処理
                conf->player_dir_char = conf->map[y][x];
                conf->player_x = x;
                conf->player_y = y;
                conf->map[y][x] = '0';
            }
            x++;
        }
        y++;
    }
    if (conf->player_dir_char == 0)
        return (FALSE);
    conf->player_init_dir = dir_to_angle(conf->player_dir_char);
    return (TRUE);
}


static char **dup_map(char **map)
{
    int row;
    char **res;
    int y;

    row = 0;
    while (map[row])
        row++;
    res = (char **)malloc(sizeof(char *) * (row + 1));
    if (!res)
        return (NULL);
    y = 0;
    while (y < row)
    {
        res[y] = ft_strdup(map[y]);
        if (!res[y])
        {
            while (y > 0)
                free(res[--y]);
            free(res);
            return (NULL);       
        }
        y++;
    }
    res[y] = NULL;
    return (res);
}

static t_bool fload_fill(char **map, int x, int y)
{
    if (y < 0 || x < 0)
        return (TRUE);
    if (!map[y])
        return (TRUE);
    if (x >= (int)ft_strlen(map[y]))
        return (TRUE);
    
    if (map[y][x] == ' ')
        return (TRUE);
    
    if (map[y][x] == '1' || map[y][x] == 'V')
        return (FALSE);
    
    map[y][x] = 'V';

    if (fload_fill(map, x, y - 1))
        return (TRUE);
    if (fload_fill(map, x, y + 1))
        return (TRUE);
    if (fload_fill(map, x + 1, y))
        return (TRUE);
    if (fload_fill(map, x - 1, y))
        return (TRUE);
    return (FALSE);
}

t_bool is_map_closed(t_config *conf)
{
    char **cpy;
    t_bool is_leak;
    int i;

    cpy = dup_map(conf->map);
    if (!cpy)
        return (FALSE); // ### TODO: エラー処理
    is_leak = fload_fill(cpy, conf->player_x, conf->player_y);
    i = 0;
    while (cpy[i])
    {
        free(cpy[i]);
        i++;
    } 
    free(cpy);
    return (!is_leak);
}  