/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-19 02:01:18 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-19 02:01:18 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool is_config_all_set(t_config *conf)
{
    return (conf->path_n && conf->path_s && conf->path_e && conf->path_w \
                && conf->ceil_color != -1 && conf->floor_color != -1);
}

t_bool set_path(char **dst, const char *val)
{
    if (*dst != NULL)
        return (FALSE); // ### TODO: エラー処理
    *dst = ft_strdup(val);
    if (!*dst)
        return (FALSE); // ### TODO: エラー処理
    return (TRUE);
}

void free_split(char **ptr)
{
    int i;

    i = 0;
    while (ptr[i])
        free(ptr[i++]);
    free(ptr);
}

t_bool parse_rgb_part(char *color, int *dst)
{
    int i;
    int val;

    i = 0;
    val = 0;

    if (!color || !color[i])
        return (FALSE);
    while (color[i])
    {
        if (!ft_isdigit(color[i]))
            return (FALSE);
        val = val * 10 + (color[i] - '0');
        if (val > 255)
            return (FALSE);
        i++;
    }
    *dst = val;
    return (TRUE);
}

t_bool parse_rgb_to_int(char *color, int *val)
{
    char **colors;
    char *trim_color;
    int i;
    int rgb[3];

    colors = ft_split(color, ',');
    if (!colors)
        return (FALSE); // ### TODO: エラー処理
    i = 0;
    while (i < RGB_COUNT)
    {
        if (!colors[i])
            return (free_split(colors), FALSE); // ### TODO: エラー処理
        trim_color = ft_strtrim(colors[i], " \t");
        if (!trim_color)
            return (free_split(colors), FALSE); // ### TODO: エラー処理
        if (!parse_rgb_part(trim_color, &rgb[i]))
            return (free(trim_color), free_split(colors), FALSE);
        free(trim_color);
        i++;
    }
    if (colors[i] != NULL)
        return (free_split(colors), FALSE);
    *val = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
    free_split(colors);
    return (TRUE);
}

t_bool set_color(int *dst, char *color)
{  
    int val;

    if (*dst != -1)
        return (FALSE); //### TODO: エラー処理
    if (!parse_rgb_to_int(color, &val))
        return (FALSE);
    *dst = val;
    return (TRUE);
}

t_bool parse_config_line(char *line, t_config *conf)
{
    if (!ft_strncmp(line, "NO ", TEX_LABEL))
        return (set_path(&conf->path_n, line + TEX_LABEL));
    else if (!ft_strncmp(line, "SO ", TEX_LABEL))
        return (set_path(&conf->path_s, line + TEX_LABEL));
    else if (!ft_strncmp(line, "WE ", TEX_LABEL))
        return (set_path(&conf->path_w, line + TEX_LABEL));
    else if (!ft_strncmp(line, "EA ", TEX_LABEL))
        return (set_path(&conf->path_e, line + TEX_LABEL));
    else if (!ft_strncmp(line, "F ", COLOR_LABEL))
        return (set_color(&conf->floor_color, line + COLOR_LABEL));
    else if (!ft_strncmp(line, "C ", COLOR_LABEL))
        return (set_color(&conf->ceil_color, line + COLOR_LABEL));
    return (FALSE);
}

void init_config(t_config *conf)
{
    conf->path_n = NULL;
    conf->path_s = NULL;
    conf->path_e = NULL;
    conf->path_w = NULL;
    conf->ceil_color = -1;
    conf->floor_color = -1;
    conf->map = NULL;
    conf->player_dir = 0;
    conf->player_x = -1;
    conf->player_y = -1;
}

t_bool read_config(int fd, t_config *conf)
{
    char *tmp;
    char *line;

    while (1)
    {
        if (is_config_all_set(conf))
            break;
        tmp = get_next_line(fd);
        if (!tmp)  
            return (FALSE); // ### TODO: エラーor読み取り未完了処理
        line = ft_strtrim(tmp, " \t\n");
        if (!line)
            return (FALSE); // ### TODO: エラー処理
        free(tmp);
        if (!line[0])
        {
            free(line);
            continue ;
        }
        if (!parse_config_line(line, conf))
            return (free(line), FALSE); // ### TODO: エラー処理
        free(line);
    }
    return (TRUE);
}

static void chomp_nl(char *s)
{
    size_t len;

    if (!s)
        return ;
    len = ft_strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}

void free_node_only(void *content)
{
    (void)content;
}

t_bool list_to_map(t_list *list, t_config *conf)
{
    int i;
    t_list *cur;

    conf->map = (char **)malloc(sizeof(char *) * (ft_lstsize(list) + 1));
    if (!conf->map)
        return (FALSE);
    i = 0;
    cur = list;
    while (cur)
    {
        conf->map[i++] = (char *)cur->content;
        cur = cur->next;
    }
    conf->map[i] = NULL;
    return (TRUE);
}

t_bool read_map(int fd, t_config *conf)
{
    char *line;
    t_bool is_start;
    t_list *list;
    t_list *node;

    is_start = FALSE;
    list = NULL;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        chomp_nl(line);
        if (!is_start && line[0] == '\0')
        {
            free(line);
            continue ;
        }
        if (is_start && line[0] == '\0')
            return (free(line), ft_lstclear(&list, free), FALSE); // ### TODO: エラー処理
        is_start = TRUE;
        node = ft_lstnew(line);
        if (!node)
            return (free(line), ft_lstclear(&list, free), FALSE);
        ft_lstadd_back(&list, node);
    }
    if (!is_start)
        return (FALSE);
    
    if (!list_to_map(list, conf))
        return (ft_lstclear(&list, free), FALSE);

    ft_lstclear(&list, free_node_only);
    return (TRUE);
}

t_bool is_player_char(const char c)
{
    return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

t_bool is_valid_map_char(const char c)
{
    return (is_player_char(c) || c == '1' || c == '0' || c == ' ');
}

double dir_to_angle(const char c)
{
    if (c == 'E')
        return (0.0);
    if (c == 'S')
        return (PI / 2);
    if (c == 'W')
        return (PI);
    if (c == 'N')
        return (PI / 2 * PI);
    return (0.0);
}

t_bool detect_player(t_config *conf)
{
    int y;
    int x;
    
    y = 0;
    while (conf->map && conf->map[y])
    {
        x = 0;
        while (conf->map[y][x])
        {
            if (!is_valid_map_char(conf->map[y][x]))
                return (FALSE); // ### TODO: エラー処理
            if (is_player_char(conf->map[y][x]))
            {
                if (conf->player_dir != 0)
                    return (FALSE); // ### TODO: エラー処理
                conf->player_dir = conf->map[y][x];
                conf->player_x = x;
                conf->player_y = y;
                conf->map[y][x] = '0';
            }
            x++;
        }
        y++;
    }
    if (conf->player_dir == 0)
        return (FALSE);
    conf->player_dir = dir_to_angle(conf->player_dir);
    return (TRUE);
}

char **dup_map(char **map)
{
    int row;
    char **res;
    int y;

    row = 0;
    while (map[row])
        row++;
    res = (char **)malloc(sizeof(char *) * (row + 1));
    if (!res)
        return (NULL);
    y = 0;
    while (y < row)
    {
        res[y] = ft_strdup(map[y]);
        if (!res[y])
        {
            while (y > 0)
                free(res[--y]);
            free(res);
            return (NULL);       
        }
        y++;
    }
    res[y] = NULL;
    return (res);
}

t_bool fload_fill(char **map, int x, int y)
{
    if (y < 0 || x < 0)
        return (TRUE);
    if (!map[y])
        return (TRUE);
    if (x >= (int)ft_strlen(map[y]))
        return (TRUE);
    
    if (map[y][x] == ' ')
        return (TRUE);
    
    if (map[y][x] == '1' || map[y][x] == 'V')
        return (FALSE);
    
    map[y][x] = 'V';

    if (fload_fill(map, x, y - 1))
        return (TRUE);
    if (fload_fill(map, x, y + 1))
        return (TRUE);
    if (fload_fill(map, x + 1, y))
        return (TRUE);
    if (fload_fill(map, x - 1, y))
        return (TRUE);
    return (FALSE);
}

t_bool is_map_closed(t_config *conf)
{
    char **cpy;
    t_bool is_leak;
    int i;

    cpy = dup_map(conf->map);
    if (!cpy)
        return (FALSE); // ### TODO: エラー処理
    is_leak = fload_fill(cpy, conf->player_x, conf->player_y);
    i = 0;
    while (cpy[i])
    {
        free(cpy[i]);
        i++;
    } 
    free(cpy);
    return (!is_leak);
}  

t_bool read_file(char *file_name, t_config *conf)
{
    const int fd = open(file_name, O_RDONLY);

    if (fd < 0)
        return (FALSE); // ### TODO: エラー処理
    init_config(conf);
    if (!read_config(fd, conf))
        return (close(fd), FALSE);
    if (!read_map(fd, conf))
        return (close(fd), FALSE);
    if (!detect_player(conf))
        return (close(fd), FALSE);
    if (!is_map_closed(conf))
        return (close(fd), FALSE);
    close(fd);
    return (TRUE);
}