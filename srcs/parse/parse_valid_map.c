/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:23:15 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/28 13:11:58 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**dup_map(char **map)
{
	int		row;
	char	**res;
	int		y;

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

static t_leak	flood_fill(char **map, int x, int y)
{
	t_leak	res;

	if (y < 0 || x < 0)
		return (LEAK_OUT);
	if (!map[y] || x >= (int)ft_strlen(map[y]))
		return (LEAK_OUT);
	if (map[y][x] == ' ')
		return (LEAK_SPACE);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (LEAK_NONE);
	map[y][x] = 'V';
	res = flood_fill(map, x, y - 1);
	if (res != LEAK_NONE)
		return (res);
	res = flood_fill(map, x, y + 1);
	if (res != LEAK_NONE)
		return (res);
	res = flood_fill(map, x + 1, y);
	if (res != LEAK_NONE)
		return (res);
	res = flood_fill(map, x - 1, y);
	if (res != LEAK_NONE)
		return (res);
	return (LEAK_NONE);
}

t_bool	is_map_closed(t_config *conf)
{
	char	**cpy;
	t_leak	leak;
	int		i;

	cpy = dup_map(conf->map);
	if (!cpy)
	{
		print_error(MAP_LABEL, "malloc failed.");
		return (FALSE);
	}
	leak = flood_fill(cpy, conf->player_x, conf->player_y);
	if (leak == LEAK_OUT)
		print_error(MAP_LABEL, "not closed by walls.");
	else if (leak == LEAK_SPACE)
		print_error(MAP_LABEL, "contains a space.");
	i = 0;
	while (cpy[i])
	{
		free(cpy[i]);
		i++;
	}
	free(cpy);
	return (leak == LEAK_NONE);
}
