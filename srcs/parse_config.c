/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:19:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/25 13:50:10 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	is_config_all_set(t_config *conf)
{
	return (conf->path_n && conf->path_s && conf->path_e && conf->path_w
		&& conf->ceil_color != -1 && conf->floor_color != -1);
}

static t_bool	set_path(char **dst, char *val)
{
	char	*trim;

	if (*dst != NULL)
	{
		print_error_detail("Config: duplicate texture identifier.", val);
		return (FALSE);
	}
	trim = ft_strtrim(val, " \t");
	*dst = trim;
	if (!*dst)
	{
		print_error("Config: malloc failed.");
		return (FALSE);
	}
	return (TRUE);
}

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

static t_bool	set_color(int *dst, char *color)
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

static t_bool parse_config_line(char *line, t_config *conf)
{	
	size_t i;
	const t_rule rules[] = {
		{NORTH_TEX_LAB, &conf->path_n, set_path}, 
		{SOUTH_TEX_LAB, &conf->path_s, set_path},
		{WEST_TEX_LAB, &conf->path_w, set_path},
		{EAST_TEX_LAB, &conf->path_e, set_path},
	};
	const size_t rule_size = sizeof(rules) / sizeof(rules[0]);
	i = 0;
	while (i < rule_size)
	{
		if (!ft_strncmp(rules[i].label, line, TEX_LAB_LEN))
			return (rules[i].handler(rules[i].dst, line + TEX_LAB_LEN));
		i++;
	}
	if (!ft_strncmp(line, FLOOR_TEX_LAB, COLOR_LAB_LEN))
		return (set_color(&conf->floor_color, line + COLOR_LAB_LEN));
	else if (!ft_strncmp(line, CEIL_TEX_LAB, COLOR_LAB_LEN))
		return (set_color(&conf->ceil_color, line + COLOR_LAB_LEN));
	print_error_detail("Config: invalid identifer.", line);
	return (FALSE);
}

t_bool	read_config(int fd, t_config *conf)
{
	char	*tmp;
	char	*line;

	while (!is_config_all_set(conf))
	{
		tmp = get_next_line(fd);
		if (!tmp)
			return (print_error("Config: incomplete."), FALSE);
		line = ft_strtrim(tmp, " \t\n");
		free(tmp);
		if (!line)
			return (print_error("Config: malloc failed."), FALSE);
		if (!line[0])
		{
			free(line);
			continue ;
		}
		if (!parse_config_line(line, conf))
			return (free(line), FALSE);
		free(line);
	}
	return (TRUE);
}
