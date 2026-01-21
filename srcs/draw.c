/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-18 08:18:50 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-18 08:18:50 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
    dst = img->addr + y * img->size_line + x * (img->bpp / 8);
    *(unsigned int *)dst = color;
}

void draw_square(int x, int y, int size, int color, t_img *img) 
{
    for (int i = 0; i < size; i++)
        put_pixel(img, x + i, y, color);
    for (int i = 0; i < size; i++)
        put_pixel(img, x + i, y + size, color);
    for (int i = 0; i < size; i++)
        put_pixel(img, x, y + i, color);
    for (int i = 0; i < size; i++)
        put_pixel(img, x + size, y + i, color);
}

void clear_image(t_img *img)
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            put_pixel(img, j, i, 0x000000);
}

// void draw_wall_split(t_img *img ,int x, int top, int bottom, int color)
// {
//     if (top < 0) 
//         top = 0;
//     if (bottom >= HEIGHT) 
//         bottom = HEIGHT - 1;
//     for (int y = top; y <= bottom; y++)
//         put_pixel(img, x, y, color);
// }