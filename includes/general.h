/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:37:27 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/27 15:43:17 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

typedef int		t_bool;
# define TRUE 1
# define FALSE 0

// read file
# define TEX_LAB_LEN 3
# define COLOR_LAB_LEN 2
# define RGB_COUNT 3

# define WEST_TEX_LAB "WE "
# define EAST_TEX_LAB "EA "
# define SOUTH_TEX_LAB "SO "
# define NORTH_TEX_LAB "NO "
# define FLOOR_TEX_LAB "F "
# define CEIL_TEX_LAB "C "

// parse - error 
# define ERR_LABEL "Error: "
# define CONF_LABEL "Config: "
# define MAP_LABEL "Map: "
# define MLX_LABEL "mlx: "

# define CUB_FILE_EXT ".cub"
# define CUB_EXT_LEN 4

#endif