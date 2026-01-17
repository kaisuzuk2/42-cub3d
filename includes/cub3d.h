/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-16 05:59:17 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-16 05:59:17 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "mlx.h"
#include "game.h"
#include "math.h"
#include <unistd.h>
#include <stdlib.h>

# define TILE_SIZE 64

# define PI 3.14159265
# define TWO_PI 6.28318530

// /usr/include/X11/keysymdef.h
# define XK_W 0x0077
# define XK_A 0x0061
# define XK_S 0x0073
# define XK_D 0x0064
# define XK_LEFT 0xff51
# define XK_RIGHT 0xff53

// /usr/include/X11/X.h
# define KEYPRESS 2
# define KEYRELEASE 3

#endif