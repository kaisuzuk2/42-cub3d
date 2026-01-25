/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:59:47 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/25 14:03:44 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	is_player_char(const char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}


static t_bool	is_valid_map_char(const char c)
{
	return (is_player_char(c) || c == '1' || c == '0' || c == ' ');
}

static double	dir_to_angle(const char c)
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


static t_bool	register_player_at(t_config *conf, int x, int y)
{
	if (conf->player_dir_char != 0)
	{
        print_error("Map: multiple player positions.");
        return (FALSE);
    }
	conf->player_dir_char = conf->map[y][x];
	conf->player_x = x;
	conf->player_y = y;
	conf->map[y][x] = '0';
	return (TRUE);
}

t_bool	setup_player_from_map(t_config *conf)
{
	int	y;
	int	x;

	y = 0;
	while (conf->map && conf->map[y])
	{
		x = 0;
		while (conf->map[y][x])
		{
			if (!is_valid_map_char(conf->map[y][x]))
				return (print_error_detail("Map: invalid map character", \
						&conf->map[y][x]), FALSE); 
			if (is_player_char(conf->map[y][x]))
				if (!register_player_at(conf, x, y))
					return (FALSE);
			x++;
		}
		y++;
	}
	if (conf->player_dir_char == 0)
		return (print_error("Map: player not found."), FALSE); 
	conf->player_init_dir = dir_to_angle(conf->player_dir_char);
	return (TRUE);
}
