/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:22:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/26 09:37:55 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	parse_rgb_part(char *color, int *dst)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
		{
			print_error_detail("Config: invalid color value", color);
			return (FALSE);
		}
		val = val * 10 + (color[i] - '0');
		if (val > 255)
		{
			print_error_detail("Config: color value out of range", color);
			return (FALSE);
		}
		i++;
	}
	*dst = val;
	return (TRUE);
}

static t_bool	parse_one_rgb(char *color, int *dst)
{
	char	*trim;
	t_bool	res;

	trim = ft_strtrim(color, " \t");
	if (!trim)
		return (print_error("Config: malloc failed."), FALSE);
	res = parse_rgb_part(trim, dst);
	free(trim);
	return (res);
}

static t_bool	parse_rgb_to_int(char *color, int *val)
{
	char	**colors;
	int		i;
	int		rgb[3];

	colors = ft_split(color, ',');
	if (!colors)
		return (print_error("Config: malloc failed."), FALSE);
	i = 0;
	while (i < RGB_COUNT)
	{
		if (!colors[i])
			break ;
		if (!parse_one_rgb(colors[i], &rgb[i]))
			return (free_split(colors), FALSE);
		i++;
	}
	if (i != RGB_COUNT || colors[i] != NULL)
	{
		free_split(colors);
		print_error_detail("Config: color format error", color);
		return (FALSE);
	}
	*val = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	free_split(colors);
	return (TRUE);
}

t_bool	set_color(int *dst, char *color)
{
	int	val;

	if (*dst != -1)
	{
		print_error_detail("Config: duplicate color identifier", color);
		return (FALSE);
	}
	if (!parse_rgb_to_int(color, &val))
		return (FALSE);
	*dst = val;
	return (TRUE);
}
