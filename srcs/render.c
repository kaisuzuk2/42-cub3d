/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-18 08:20:46 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-18 08:20:46 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void draw_background_strip(t_game *game, int x, int top, int bottom)
{
    int y;

    y = 0;
    while (y < top)
    {
        put_pixel(&game->img, x, y, game->conf.ceil_color);
        y++;
    }
    y = bottom + 1;
    while (y < HEIGHT)
    {
        put_pixel(&game->img, x, y, game->conf.floor_color);
        y++;
    }
}

// fisheye
// cos = fromt / dist
static float calc_perp_dist(t_ray *ray, float player_angle)
{
    float res;

    res = ray->distance * cosf(ray->ray_angle - player_angle);
    if (res < 0.0001f)
        res = 0.0001f;
    return (res);
}

static void calc_wall(float perp_dist, int *top, int *bottom)
{
    const float fov = PI / 3.0f;
    const float dist_proj = (WIDTH / 2.0f) / tanf(fov / 2.0f);
    float proj_wall_h;
    int wall_h;

    proj_wall_h = (TILE_SIZE / perp_dist) * dist_proj;
    wall_h = (int)proj_wall_h;
    *top = (HEIGHT / 2) - (wall_h / 2);
    *bottom = (HEIGHT / 2) + (wall_h / 2);
    if (*top < 0)
        *top = 0;
    if (*bottom >= HEIGHT)
        *bottom = HEIGHT - 1;
}

static int get_tex_x(t_ray *ray, t_tex *tex)
{
    float hit;
    int tex_x;

    if (ray->was_hit_vertical)
        hit = ray->wall_hit_y;
    else
        hit = ray->wall_hit_x;
    tex_x = (int)fmodf(hit, TILE_SIZE);
    tex_x = (int)((float)tex_x * tex->w / TILE_SIZE);
    return (tex_x);
}

static void draw_wall_split(t_game *game, int i, int top, int bottom)
{
    t_tex *tex;
    int tex_x;
    int y;
    int dist_from_top;
    int tex_y;

    tex = select_wall_tex(game, &game->player.ray[i]);
    tex_x = get_tex_x(&game->player.ray[i], tex);
    y = top;
    while (y <= bottom)
    {
        dist_from_top = y - top;
        tex_y = (int)((float)dist_from_top * tex->h / (bottom - top + 1)); 
        put_pixel(&game->img, i, y, get_texel(tex, tex_x, tex_y));
        y++;
    }
}

static void render_3d_walls(t_game *game)
{
    float perp_dist;
    int top;
    int bottom;

    for (int i = 0; i < NUM_RAYS; i++)
    {
        perp_dist = calc_perp_dist(&game->player.ray[i], game->player.angle);
        calc_wall(perp_dist, &top, &bottom);
        draw_background_strip(game, i, top, bottom);
        draw_wall_split(game, i, top, bottom);
    }
}


int render(t_game *game) 
{
    clear_image(&game->img);
    cast_all_rays(&game->player, game->conf.map);
    render_3d_walls(game);
    move_player(&game->player, game->conf.map);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
    return (0);
}