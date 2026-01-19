/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:39:50 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/06 17:32:02 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

char	*ft_gnl_strchr(const char *s, int c);
char	*ft_gnl_strndup(const char *s, size_t n);
char	*ft_gnl_strdup(const char *s);
char	*ft_gnl_strjoin(char const *s1, char const *s2);
size_t	ft_gnl_strlen(const char *s);

char	*get_next_line(int fd);

#endif