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

static void render_3d_walls(t_game *game)
{
    const float fov = PI / 3.0f;
    const float dist_proj_plane = (WIDTH / 2.0f) / tanf(fov / 2.0f);

    for (int i = 0; i < NUM_RAYS; i++)
    {
        // fisheye
        // cos = 正面 / dist
        float perp_dist = game->player.ray[i].distance * cosf(game->player.ray[i].ray_angle - game->player.angle);

        // 壁が近すぎる時の補正
        if (perp_dist < 0.0001f)
            perp_dist = 0.0001f;

        // 壁の高さ
        float proj_wall_h = (TILE_SIZE / perp_dist) * dist_proj_plane;
        int wall_h = (int)proj_wall_h;

        int top = (HEIGHT / 2) - (wall_h / 2);
        int bottom = (HEIGHT / 2) + (wall_h / 2);

        // テクスチャ
        float hit = game->player.ray[i].was_hit_vertical ? game->player.ray[i].wall_hit_y: \
                                                                game->player.ray[i].wall_hit_x;
        t_tex *tex = select_wall_tex(game, &game->player.ray[i]);
        int tex_x = (int)fmodf(hit, TILE_SIZE);
        tex_x = (int)((float)tex_x * tex->w / TILE_SIZE);

        if (top < 0)
            top = 0;
        if (bottom >= HEIGHT)
            bottom = HEIGHT - 1;
        // 天井
        for (int y = 0; y < top; y++)
            put_pixel(&game->img, i, y, 0x003333);
        
        // 壁
        for (int y = top; y <= bottom; y++)
        {
            int dist_from_top = y - top;
            // テクスチャの座標へスケール
            int tex_y = (int)((float)dist_from_top * tex->h / (bottom - top + 1));

            unsigned int color = get_texel(tex, tex_x, tex_y);
            put_pixel(&game->img, i, y, color);
        }

        // 床
        for (int y = bottom + 1; y < HEIGHT; y++)
            put_pixel(&game->img, i, y, 0x006666);
        // int color = game->player.ray[i].was_hit_vertical ? 0x00CCCC: 0x00FFFF;


        // draw_wall_split(&game->img, i, top, bottom, color);
    }
}

int render(t_game *game) 
{
    clear_image(&game->img);
    cast_all_rays(&game->player, game->map);
    render_3d_walls(game);
    move_player(&game->player, game->map);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
    return (0);
}