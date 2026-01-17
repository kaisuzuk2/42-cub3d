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
    return (TRUE);
}

void setup(t_game *game) {
    game->player.x = WIDTH / 2;
    game->player.y = HEIGHT / 2;
    game->player.width = 5;
    game->player.height = 5;
    game->player.turn_direction = 0;
    game->player.walk_direction = 0;
    game->player.rotation_angle = PI / 2;
    game->player.walk_speed = 100;
    game->player.turn_spead = 45 * (PI / 180);

    game->player.key_up = FALSE;
    game->player.key_down = FALSE;
    game->player.key_left = FALSE;
    game->player.key_right = FALSE;
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
    return (0);
}

void move_player(t_player *player)
{
    const int speed = 5;

    if (player->key_up)
        player->y -= speed;
    if (player->key_down)
        player->y += speed;
    if (player->key_left)
        player->x -= speed;
    if (player->key_right)
        player->x += speed;
}

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

void render_map(t_game *game) {
    char **map = get_map();
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
    draw_square(player->x, player->y, player->width, 0xFF0000, img);
}

int render(t_game *game) {
    render_map(game);
    render_player(&game->player, &game->img);
    move_player(&game->player);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
    return (0);
}

int main(void)
{
    t_game game;
    init(&game);
    setup(&game);
    mlx_hook(game.win, KEYPRESS, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, KEYRELEASE, 1L<<0, key_release, &game.player);
    mlx_loop_hook(game.mlx, render, &game);
    mlx_loop(game.mlx);
    return (0);
}