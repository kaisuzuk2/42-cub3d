/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 02:01:18 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/26 13:35:25 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	read_file(char *file_name, t_config *conf)
{
	const int	fd = open(file_name, O_RDONLY);

	if (fd < 0)
	{
		print_sys_error("open");
		return (FALSE);
	}
	if (!read_config(fd, conf))
		return (close(fd), FALSE);
	if (!read_map(fd, conf))
		return (close(fd), FALSE);
	if (!setup_player_from_map(conf))
		return (close(fd), FALSE);
	if (!is_map_closed(conf))
		return (close(fd), FALSE);
	close(fd);
	return (TRUE);
}
