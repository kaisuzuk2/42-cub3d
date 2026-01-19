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

t_bool read_file(char *file_name, t_config *conf)
{
    const int fd = open(file_name, O_RDONLY);
    char *line;
    char *tmp;

    if (fd < 0)
        return (FALSE); // ### TODO: エラー処理
    init_config(conf);
    if (!read_config(fd, conf))
        return (close(fd), FALSE);
    if (!read_map(fd, conf))
        return (close(fd), FALSE);
    close(fd);
    return (TRUE);
}