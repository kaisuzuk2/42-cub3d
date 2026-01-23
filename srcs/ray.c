/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 08:05:18 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/23 13:28:04 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float normalize_angle(float angle)
{
    angle = fmodf(angle, TWO_PI);
    if (angle < 0)
        angle += TWO_PI;
    return (angle);
}

// static void cast_ray(t_player *player, float ray_angle, char **map, int id)
// {
//     ray_angle = normalize_angle(ray_angle);
    
//     int facing_down = (ray_angle > 0 && ray_angle < PI);
//     int facing_up = !facing_down;
//     // 0.5 * PI = PI / 2 右半分
//     int facing_right = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
//     int facing_left = !facing_right;

//     float yintercept;
//     float xintercept;
//     yintercept = floorf(player->y / TILE_SIZE) * TILE_SIZE;
//     if (facing_down)
//         yintercept += TILE_SIZE;
//     // tan = tate / yoko -> yoko = tate / tan
//     xintercept = player->x + (yintercept - player->y) / tanf(ray_angle);

//     float ystep;
//     ystep = TILE_SIZE;
//     if (facing_up)
//         ystep *= -1;
//     float xstep;
//     xstep = TILE_SIZE / tanf(ray_angle);
//     if (facing_left && xstep > 0)
//         xstep *= -1;
//     if (facing_right && xstep < 0)
//         xstep *= -1;

//     float next_horz_touch_x;
//     float next_horz_touch_y;

//     next_horz_touch_x = xintercept;
//     next_horz_touch_y = yintercept;


//     int found_horz_hit = FALSE;
//     float horz_hit_x = 0;
//     float horz_hit_y = 0;

//     // while (next_horz_touch_x >= 0 && next_horz_touch_x < WIDTH 
//     //     && next_horz_touch_y >= 0 && next_horz_touch_y < HEIGHT)
//     while (1)
//     {
//         float x_to_check = next_horz_touch_x;
//         float y_to_check = next_horz_touch_y;

//         if (facing_up)
//             y_to_check -= 1;

//         if (map_has_wall_at(x_to_check, y_to_check, map))
//         {
//             found_horz_hit = TRUE;
//             horz_hit_x = next_horz_touch_x;
//             horz_hit_y = next_horz_touch_y;
//             // put_pixel(img, next_horz_touch_x, next_horz_touch_y, 0xFF0000);
//             break;
//         }
//         next_horz_touch_x += xstep;
//         next_horz_touch_y += ystep;
//     }    

// // -----

//     float vert_xintercept;
//     float vert_yintercept;

//     vert_xintercept = floorf(player->x / TILE_SIZE) * TILE_SIZE;

//     if (facing_right)
//         vert_xintercept += TILE_SIZE;
    
//     vert_yintercept = player->y + (vert_xintercept - player->x) * tanf(ray_angle);


//     float vert_xstep;
//     float vert_ystep;

//     vert_xstep = TILE_SIZE;
//     if (facing_left)
//         vert_xstep *= -1;

//     vert_ystep = TILE_SIZE * tanf(ray_angle);

//     if (facing_up && vert_ystep > 0)
//         vert_ystep *= -1;
//     if (facing_down && vert_ystep < 0)
//         vert_ystep *= -1;

//     int found_vert_hit = FALSE;
//     float vert_hit_x = 0;
//     float vert_hit_y = 0;

//     float next_vert_touch_x = vert_xintercept;
//     float next_vert_touch_y = vert_yintercept;

//     // while (next_vert_touch_x >= 0 && next_vert_touch_x < WIDTH 
//     //         && next_vert_touch_y >= 0 && next_vert_touch_y < HEIGHT)
//     while (1)
//     {
//         float x_to_check = next_vert_touch_x;
//         float y_to_check = next_vert_touch_y;

//         if (facing_left)
//             x_to_check -= 1;
        
//         if (map_has_wall_at(x_to_check, y_to_check, map))
//         {
//             found_vert_hit = TRUE;
//             vert_hit_x = next_vert_touch_x;
//             vert_hit_y = next_vert_touch_y;
//             // put_pixel(img, next_vert_touch_x, next_vert_touch_y, 0xFF0000);
//             break;
//         }
//         next_vert_touch_x += vert_xstep;
//         next_vert_touch_y += vert_ystep;
//     }

//     // -----

//     float horz_dist = INFINITY;
//     float vert_dist = INFINITY;

//     if (found_horz_hit)
//     {
//         float dx = horz_hit_x - player->x;
//         float dy = horz_hit_y - player->y;
//         horz_dist = sqrt(dx * dx + dy * dy);
//     }
//     if (found_vert_hit)
//     {
//         float dx = vert_hit_x - player->x;
//         float dy = vert_hit_y - player->y;
//         vert_dist = sqrt(dx * dx + dy * dy);
//     }

//     float final_hit_x;
//     float final_hit_y;
//     float final_dist;
//     int hit_vertical;

//     final_hit_x = vert_hit_x;
//     final_hit_y = vert_hit_y;
//     final_dist = vert_dist;
//     hit_vertical = TRUE;

//     if (horz_dist < vert_dist)
//     {
//         final_hit_x = horz_hit_x;
//         final_hit_y = horz_hit_y;
//         final_dist = horz_dist;
//         hit_vertical = FALSE;
//     }

//     player->ray[id].ray_angle = ray_angle;
//     player->ray[id].distance = final_dist;
//     player->ray[id].wall_hit_x = final_hit_x;
//     player->ray[id].wall_hit_y = final_hit_y;
//     player->ray[id].was_hit_vertical = hit_vertical;

//     player->ray[id].is_facing_up = facing_up;
//     player->ray[id].is_facing_down = facing_down;
//     player->ray[id].is_facing_left = facing_left;
//     player->ray[id].is_facing_right = facing_right;
// }

static void init_ray_dir(float ray_angle, t_ray_dir *dir)
{
    dir->is_facing_down = (ray_angle > 0 && ray_angle < PI);
    dir->is_facing_up = !dir->is_facing_down;
    dir->is_facing_right = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
    dir->is_facing_left = !dir->is_facing_right;
}

static void init_horz_intercept(t_player *player, float ray_angle, t_ray_dir *dir, t_intercept *horz)
{
    horz->y = floorf(player->y / TILE_SIZE) * TILE_SIZE;
    if (dir->is_facing_down)
        horz->y += TILE_SIZE;
    horz->x = player->x + (horz->y - player->y) / tanf(ray_angle);
    horz->ystep = TILE_SIZE;
    if (dir->is_facing_up)
        horz->ystep *= -1;
    horz->xstep = TILE_SIZE / tanf(ray_angle);
    if (dir->is_facing_left && horz->xstep > 0)
        horz->xstep *= -1;
    if (dir->is_facing_right && horz->xstep < 0)
        horz->xstep *= -1;
}

static void init_vert_intercept(t_player *player, float ray_angle, t_ray_dir *dir, t_intercept *vert)
{
    vert->x = floorf(player->x / TILE_SIZE) * TILE_SIZE;
    if (dir->is_facing_right)
        vert->x += TILE_SIZE;
    vert->y = player->y + (vert->x - player->x) * tanf(ray_angle);
    vert->xstep = TILE_SIZE;
    if (dir->is_facing_left)
        vert->xstep *= -1;
    vert->ystep = TILE_SIZE * tanf(ray_angle);
    if (dir->is_facing_up && vert->ystep > 0)
        vert->ystep *= -1;
    if (dir->is_facing_down && vert->ystep < 0)
        vert->ystep *= -1;
}

static t_bool is_hit_horz_wall(t_intercept *horz, t_ray_dir *dir, char **map, t_hit *hit)
{
    float x_check;
    float y_check;

    x_check = horz->x;
    y_check = horz->y;
    if (dir->is_facing_up)
        y_check -= 1;
    if (map_has_wall_at(x_check, y_check, map))
    {
        hit->x = horz->x;
        hit->y = horz->y;
        return (TRUE);
    }    
    return (FALSE);
}

static t_bool is_hit_vert_wall(t_intercept *vert, t_ray_dir *dir, char **map, t_hit *hit)
{
    float x_check;
    float y_check;

    x_check = vert->x;
    y_check = vert->y;
    if (dir->is_facing_left)
        x_check -= 1;
    if (map_has_wall_at(x_check, y_check, map))
    {
        hit->x = vert->x;
        hit->y = vert->y;
        return (TRUE);
    }
    return (FALSE);
}

static void find_horz_hit(t_intercept *horz, t_ray_dir *dir, char **map, t_hit *hit)
{
    hit->is_found = FALSE;
    hit->x = 0;
    hit->y = 0;
    while (1)
    {
        if (is_hit_horz_wall(horz, dir, map, hit))
        {
            hit->is_found = TRUE;
            break;
        }
        horz->x += horz->xstep;
        horz->y += horz->ystep;
    }
}

static void find_vert_hit(t_intercept *vert, t_ray_dir *dir, char **map, t_hit *hit)
{
    hit->is_found = FALSE;
    hit->x = 0;
    hit->y = 0;
    while (1)
    {
        if (is_hit_vert_wall(vert, dir, map, hit))
        {
            hit->is_found = TRUE;
            break;
        }
        vert->x += vert->xstep;
        vert->y += vert->ystep;
    }
}

static float calc_dist(t_player *player, t_hit *hit)
{
    float dx;
    float dy;

    if (!hit->is_found)
        return (INFINITY);
    dx = hit->x - player->x;
    dy = hit->y - player->y;
    return (sqrt(dx * dx + dy * dy));
}

static void choose_closest_hit(t_ray_calc *calc)
{
    if (calc->horz_dist < calc->vert_dist)
    {
        calc->final.x = calc->horz_hit.x;
        calc->final.y = calc->horz_hit.y;
        calc->final.dist = calc->horz_dist;
        calc->final.is_vertical = FALSE;
    }
    else
    {
        calc->final.x = calc->vert_hit.x;
        calc->final.y = calc->vert_hit.y;
        calc->final.dist = calc->vert_dist;
        calc->final.is_vertical = TRUE;
    }
}

static void store_ray_data(t_player *player, int id, t_ray_calc *calc, t_ray_dir *dir)
{
    player->ray[id].distance = calc->final.dist;
    player->ray[id].wall_hit_x = calc->final.x;
    player->ray[id].wall_hit_y = calc->final.y;
    player->ray[id].was_hit_vertical = calc->final.is_vertical;
    player->ray[id].is_facing_up = dir->is_facing_up;
    player->ray[id].is_facing_down = dir->is_facing_down;
    player->ray[id].is_facing_left = dir->is_facing_left;
    player->ray[id].is_facing_right = dir->is_facing_right;
}

static void cast_ray(t_player *player, float ray_angle, char **map, int id)
{
    t_ray_dir dir;
    t_ray_calc calc;

    ray_angle = normalize_angle(ray_angle);
    init_ray_dir(ray_angle, &dir);
    init_horz_intercept(player, ray_angle, &dir, &calc.horz);
    init_vert_intercept(player, ray_angle, &dir, &calc.vert);
    find_horz_hit(&calc.horz, &dir, map, &calc.horz_hit);
    find_vert_hit(&calc.vert, &dir, map, &calc.vert_hit);
    calc.horz_dist = calc_dist(player, &calc.horz_hit);
    calc.vert_dist = calc_dist(player, &calc.vert_hit);
    choose_closest_hit(&calc);
    player->ray[id].ray_angle = ray_angle;
    store_ray_data(player, id, &calc, &dir);
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
