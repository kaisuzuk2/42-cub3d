/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-16 06:03:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-01-16 06:03:57 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define WIDTH 1280
# define HEIGHT 720

typedef struct s_game {
    void *mlx;
    void *win;
    void *img;
} t_game;

#endif