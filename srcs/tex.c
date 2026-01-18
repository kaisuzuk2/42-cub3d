/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-18 05:08:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-18 05:08:07 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int get_texel(t_tex *tex, int x, int y)
{
    char *dst;

    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x >= tex->w)
        x = tex->w - 1;
    if (y >= tex->h)
        y = tex->h - 1;
    dst = tex->addr + y * tex->size_line + x * (tex->bpp / 8);
    return (*(unsigned int *)dst);
}