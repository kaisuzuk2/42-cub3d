/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 05:59:17 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/27 15:40:04 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include "general.h"
# include "game.h"
# include "externs.h"
# include "get_next_line.h"
# include "libft.h"
# include "math.h"
# include "mlx.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILUE 1

// /usr/include/X11/keysymdef.h
# define XK_W 0x0077
# define XK_A 0x0061
# define XK_S 0x0073
# define XK_D 0x0064
# define XK_LEFT 0xff51
# define XK_RIGHT 0xff53
# define XK_ESC 0xff1b

// /usr/include/X11/X.h
# define KEYPRESS 2
# define KEYRELEASE 3
# define DESTROY_NOTIFY 17

#endif