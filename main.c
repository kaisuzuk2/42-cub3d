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
        for (int j = 0; map[j]; j++)
        {
            if (map[i][j] == 1)
                draw_square(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, 0x00FF00, &game->img);
        }
    }
}

void render_player(t_player *player, t_img *img) {
    draw_square(player->x, player->y, 30, 0xFF0000, img);
}

void render(t_game *game) {
    render_map(game);
    render_player(&game->player, &game->img);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
}

int main(void)
{
    t_game game;
    init(&game);
    setup(&game);
    render(&game);
    mlx_loop(game.mlx);
    return (0);
}