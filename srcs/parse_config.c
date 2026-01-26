/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:19:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/26 09:23:24 by kaisuzuk         ###   ########.fr       */
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
