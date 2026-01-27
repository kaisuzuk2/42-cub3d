/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:23:15 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/27 15:30:58 by kaisuzuk         ###   ########.fr       */
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

static t_bool	fload_fill(char **map, int x, int y)
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

t_bool	is_map_closed(t_config *conf)
{
	char	**cpy;
	t_bool	is_leak;
	int		i;

	cpy = dup_map(conf->map);
	if (!cpy)
	{
		print_error(MAP_LABEL, "malloc failed.");
		return (FALSE);
	}
	is_leak = fload_fill(cpy, conf->player_x, conf->player_y);
	if (is_leak)
		print_error(MAP_LABEL, "not closed by walls.");
	i = 0;
	while (cpy[i])
	{
		free(cpy[i]);
		i++;
	}
	free(cpy);
	return (!is_leak);
}
