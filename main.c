/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 05:58:20 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/25 16:00:45 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static void	init_game_data(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	;
	game->img.img_ptr = NULL;
	game->tex_n.img_ptr = NULL;
	game->tex_s.img_ptr = NULL;
	game->tex_e.img_ptr = NULL;
	game->tex_w.img_ptr = NULL;
}

static t_bool parse_arg(int argc, char **argv)
{
    size_t len;
    char *file_name;
    
    if (argc != 2 || !argv[1][0])
    {
        print_usage("Error: missing map file argument.");
        return (FALSE);
    }
    len = ft_strlen(argv[1]);
    if (len <= CUB_EXT_LEN)
    {
        print_usage("Error: invalid map file name.");
        return (FALSE);
    }
    file_name = argv[1];
    if (ft_strncmp(file_name + (len - CUB_EXT_LEN), CUB_FILE_EXT, ft_strlen(CUB_FILE_EXT)))
    {
        print_usage("Error: file must have .cub extension.");
        return (FALSE);
    }
    return (TRUE);
}

int main(int argc, char *argv[])
{
    t_game game;
    if (!parse_arg(argc, argv))
        return (EXIT_FAILUE);
    if (!read_file(argv[1], &game.conf))
        return (EXIT_FAILUE); 
    init_game_data(&game);
    if (!init(&game))
    {
        dispose_conf(&game.conf);
        return (1);
    }
    init_player(&game.player, &game.conf);
    mlx_hook(game.win, KEYPRESS, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, KEYRELEASE, 1L<<1, key_release, &game.player);
    mlx_loop_hook(game.mlx, render, &game);
    mlx_loop(game.mlx);
    return (EXIT_SUCCESS);
}