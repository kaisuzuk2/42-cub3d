/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:25:04 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/23 15:25:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_split(char **ptr)
{
    int i;

    i = 0;
    while (ptr[i])
        free(ptr[i++]);
    free(ptr);
}

void init_config(t_config *conf)
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