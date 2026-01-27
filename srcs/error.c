/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:24:20 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/27 15:34:45 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_usage(char *str)
{
	ft_putstr_fd(ERR_LABEL, STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	ft_putendl_fd("Usage: ./cub3D filename.cub", STDERR_FILENO);
}

void	print_error(char *label, char *str)
{
	ft_putstr_fd(ERR_LABEL, STDERR_FILENO);
	ft_putstr_fd(label, STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

void	print_sys_error(char *func)
{
	ft_putstr_fd(ERR_LABEL, STDERR_FILENO);
	perror(func);
}

void	print_error_detail(char *label, char *str, char *near)
{
	ft_putstr_fd(ERR_LABEL, STDERR_FILENO);
	ft_putstr_fd(label, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(" near ", STDERR_FILENO);
	ft_putendl_fd(near, STDERR_FILENO);
}
