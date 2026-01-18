/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-16 05:58:20 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-16 05:58:20 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

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

t_bool init(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (FALSE);
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
    if (!game->win)
        return (FALSE); // ### TODO: エラー処理
    game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img.img_ptr)
        return (FALSE); // ### TODO: エラー処理
    game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.size_line, &game->img.endian);
    game->map = get_map();
    return (TRUE);
}

void setup(t_game *game) {
    game->player.x = WIDTH / 2;
    game->player.y = HEIGHT / 2;
    game->player.angle = PI / 2;
    game->player.key_up = FALSE;
    game->player.key_down = FALSE;
    game->player.key_left = FALSE;
    game->player.key_right = FALSE;
    game->player.left_rotate = FALSE;
    game->player.right_rotate = FALSE;
}

int key_press(int keycode, t_player *player) \
{
    if (keycode == XK_W)
        player->key_up = TRUE;
    if (keycode == XK_S)
        player->key_down = TRUE;
    if (keycode == XK_A)
        player->key_left = TRUE;
    if (keycode == XK_D)
        player->key_right = TRUE;
    if (keycode == XK_LEFT)
        player->left_rotate = TRUE;
    if (keycode == XK_RIGHT)
        player->right_rotate = TRUE;
    return (0);
}

int key_release(int keycode, t_player *player)
{
    if (keycode == XK_W)
        player->key_up = FALSE;
    if (keycode == XK_S)
        player->key_down = FALSE;
    if (keycode == XK_A)
        player->key_left = FALSE;
    if (keycode == XK_D)
        player->key_right = FALSE;
    if (keycode == XK_LEFT)
        player->left_rotate = FALSE;
    if (keycode == XK_RIGHT)
        player->right_rotate = FALSE;
    return (0);
}

#include <stdio.h>

t_bool map_has_wall_at(double x, double y, char **map) 
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return (TRUE);
    int row;
    row = 0;
    while (map[row])
        row++;
    int col;
    col = 0;
    while (map[0][col])
        col++;
    if ((int)(y / TILE_SIZE) >= row)
        return (TRUE);
    if ((int)(x / TILE_SIZE) >= col)
        return (TRUE);
    return (map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != '0');
}

void move_player(t_player *player, char **map)
{
    const int speed = 1;
    const float angle_speed = 0.1;
    float cos_angle;
    float sin_angle;
    double dx;
    double dy;

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    if (player->angle > TWO_PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = TWO_PI;

    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);

    dx = player->x;
    dy = player->y;

    if (player->key_up)
    {
        dx += cos_angle * speed;
        dy += sin_angle * speed;
    }
    if (player->key_down)
    {
        dx -= cos_angle * speed;
        dy -= sin_angle * speed;
    }
    if (player->key_left)
    {
        dx += sin_angle * speed;
        dy -= cos_angle * speed;
    }
    if (player->key_right)
    {
        dx -= sin_angle * speed;
        dy += cos_angle * speed;
    }
    if (!map_has_wall_at(dx, dy, map))
    {
        player->x = dx;
        player->y = dy;
    }
}

float normalize_angle(float angle)
{
    angle = fmodf(angle, TWO_PI);
    if (angle < 0)
        angle += TWO_PI;
    return (angle);
}

void cast_ray(t_player *player, float ray_angle, char **map, int id)
{
    ray_angle = normalize_angle(ray_angle);
    
    int facing_down = (ray_angle > 0 && ray_angle < PI);
    int facing_up = !facing_down;
    // 0.5 * PI = PI / 2 右半分
    int facing_right = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
    int facing_left = !facing_right;

    float yintercept;
    float xintercept;
    yintercept = floorf(player->y / TILE_SIZE) * TILE_SIZE;
    if (facing_down)
        yintercept += TILE_SIZE;
    // tan = tate / yoko -> yoko = tate / tan
    xintercept = player->x + (yintercept - player->y) / tanf(ray_angle);

    float ystep;
    ystep = TILE_SIZE;
    if (facing_up)
        ystep *= -1;
    float xstep;
    xstep = TILE_SIZE / tanf(ray_angle);
    if (facing_left && xstep > 0)
        xstep *= -1;
    if (facing_right && xstep < 0)
        xstep *= -1;

    float next_horz_touch_x;
    float next_horz_touch_y;

    next_horz_touch_x = xintercept;
    next_horz_touch_y = yintercept;


    int found_horz_hit = FALSE;
    float horz_hit_x = 0;
    float horz_hit_y = 0;

    while (next_horz_touch_x >= 0 && next_horz_touch_x < WIDTH \
        && next_horz_touch_y >= 0 && next_horz_touch_y < HEIGHT)
    {
        float x_to_check = next_horz_touch_x;
        float y_to_check = next_horz_touch_y;

        if (facing_up)
            y_to_check -= 1;

        if (map_has_wall_at(x_to_check, y_to_check, map))
        {
            found_horz_hit = TRUE;
            horz_hit_x = next_horz_touch_x;
            horz_hit_y = next_horz_touch_y;
            // put_pixel(img, next_horz_touch_x, next_horz_touch_y, 0xFF0000);
            break;
        }
        next_horz_touch_x += xstep;
        next_horz_touch_y += ystep;
    }    

// -----

    float vert_xintercept;
    float vert_yintercept;

    vert_xintercept = floorf(player->x / TILE_SIZE) * TILE_SIZE;

    if (facing_right)
        vert_xintercept += TILE_SIZE;
    
    vert_yintercept = player->y + (vert_xintercept - player->x) * tanf(ray_angle);


    float vert_xstep;
    float vert_ystep;

    vert_xstep = TILE_SIZE;
    if (facing_left)
        vert_xstep *= -1;

    vert_ystep = TILE_SIZE * tanf(ray_angle);

    if (facing_up && vert_ystep > 0)
        vert_ystep *= -1;
    if (facing_down && vert_ystep < 0)
        vert_ystep *= -1;

    int found_vert_hit = FALSE;
    float vert_hit_x = 0;
    float vert_hit_y = 0;

    float next_vert_touch_x = vert_xintercept;
    float next_vert_touch_y = vert_yintercept;

    while (next_vert_touch_x >= 0 && next_vert_touch_x < WIDTH \
            && next_vert_touch_y >= 0 && next_vert_touch_y < HEIGHT)
    {
        float x_to_check = next_vert_touch_x;
        float y_to_check = next_vert_touch_y;

        if (facing_left)
            x_to_check -= 1;
        
        if (map_has_wall_at(x_to_check, y_to_check, map))
        {
            found_vert_hit = TRUE;
            vert_hit_x = next_vert_touch_x;
            vert_hit_y = next_vert_touch_y;
            // put_pixel(img, next_vert_touch_x, next_vert_touch_y, 0xFF0000);
            break;
        }
        next_vert_touch_x += vert_xstep;
        next_vert_touch_y += vert_ystep;
    }

    // -----

    float horz_dist = INFINITY;
    float vert_dist = INFINITY;

    if (found_horz_hit)
    {
        float dx = horz_hit_x - player->x;
        float dy = horz_hit_y - player->y;
        horz_dist = sqrt(dx * dx + dy * dy);
    }
    if (found_vert_hit)
    {
        float dx = vert_hit_x - player->x;
        float dy = vert_hit_y - player->y;
        vert_dist = sqrt(dx * dx + dy * dy);
    }

    float final_hit_x;
    float final_hit_y;
    float final_dist;
    int hit_vertical;

    final_hit_x = vert_hit_x;
    final_hit_y = vert_hit_y;
    final_dist = vert_dist;
    hit_vertical = TRUE;

    if (horz_dist < vert_dist)
    {
        final_hit_x = horz_hit_x;
        final_hit_y = horz_hit_y;
        final_dist = horz_dist;
        hit_vertical = FALSE;
    }

    player->ray[id].ray_angle = ray_angle;
    player->ray[id].distance = final_dist;
    player->ray[id].wall_hit_x = final_hit_x;
    player->ray[id].wall_hit_y = final_hit_y;
    player->ray[id].was_hit_vertical = hit_vertical;

    player->ray[id].is_facing_up = facing_up;
    player->ray[id].is_facing_down = facing_down;
    player->ray[id].is_facing_left = facing_left;
    player->ray[id].is_facing_right = facing_right;

}

void cast_all_rays(t_player *player, char **map) 
{
    const float fov = PI / 3.0;
    const float angle_step = fov / NUM_RAYS;
    float ray_angle = player->angle - (fov / 2);

    for (int i = 0; i < NUM_RAYS; i++) {
        cast_ray(player, ray_angle, map, i);
        ray_angle += angle_step;
    }
}

static void draw_line(t_img *img, float x0, float y0, float x1, float y1, int color)
{
    float dx = x1 - x0;
    float dy = y1 - y0;

    float steps = fabsf(dx);
    if (fabsf(dy) > steps)
        steps = fabsf(dy);

    if (steps < 1.0f)
        return;

    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = x0;
    float y = y0;

    for (int i = 0; i <= (int)steps; i++)
    {
        put_pixel(img, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }
}


void render_ray(t_player *player, t_img *img, char **map) 
{
    cast_all_rays(player, map);

    for (int i = 0; i < NUM_RAYS; i++)
    {
        if (player->ray[i].distance != INFINITY)
            draw_line(img, player->x, player->y, player->ray[i].wall_hit_x, player->ray[i].wall_hit_y, 0xFF0000);
    }
}

void render_map(t_game *game) {
    char **map = game->map;
    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j]; j++)
        {
            if (map[i][j] == '1')
                draw_square(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, 0x00FF00, &game->img);
        }
    }
}

void render_player(t_player *player, t_img *img) {
    draw_square(player->x, player->y, 10, 0xFF0000, img);
}

void clear_image(t_img *img)
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            put_pixel(img, j, i, 0x000000);
}

int render(t_game *game) {
    clear_image(&game->img);
    render_map(game);
    render_ray(&game->player, &game->img, game->map);
    render_player(&game->player, &game->img);
    move_player(&game->player, game->map);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
    return (0);
}

int main(void)
{
    t_game game;
    init(&game);
    setup(&game);
    mlx_hook(game.win, KEYPRESS, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, KEYRELEASE, 1L<<1, key_release, &game.player);
    mlx_loop_hook(game.mlx, render, &game);
    mlx_loop(game.mlx);
    return (0);
}