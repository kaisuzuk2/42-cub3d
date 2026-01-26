/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 02:01:18 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/26 09:21:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_config(t_config *conf)
{
    conf->path_n = NULL;
    conf->path_s = NULL;
    conf->path_e = NULL;
    conf->path_w = NULL;
    conf->ceil_color = -1;
    conf->floor_color = -1;
    conf->map = NULL;
    conf->player_dir_char = 0;
    conf->player_init_dir = 0.0;
    conf->player_x = -1;
    conf->player_y = -1;
}

t_bool read_file(char *file_name, t_config *conf)
{
    const int fd = open(file_name, O_RDONLY);

    if (fd < 0)
    {
        print_sys_error("open");
        return (FALSE);
    }
    init_config(conf);
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