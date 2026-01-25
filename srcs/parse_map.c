/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:21:42 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/01/25 16:34:59 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	chomp_nl(char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}

static void	free_node_only(void *content)
{
	(void)content;
}

static t_bool	list_to_map(t_list *list, t_config *conf)
{
	int		i;
	t_list	*cur;

	conf->map = (char **)malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	if (!conf->map)
	{
		print_error("Map: malloc failed.");
		return (FALSE);
	}
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

t_bool	read_map_line(t_bool *is_start, char *line, t_list **head)
{
	t_list	*node;

	if (!*is_start && line[0] == '\0')
		return (TRUE);
	if (*is_start && line[0] == '\0')
	{
		print_error("Map: empty line inside map.");
		return (FALSE);
	}
	*is_start = TRUE;
	node = ft_lstnew(line);
	if (!node)
	{
		print_error("Map: malloc failed.");
		return (FALSE);
	}
	ft_lstadd_back(head, node);
	return (TRUE);
}

t_bool	read_map(int fd, t_config *conf)
{
	char	*line;
	t_bool	is_start;
	t_list	*head;

    head = NULL;
	is_start = FALSE;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		chomp_nl(line);
		if (!read_map_line(&is_start, line, &head))
			return (free(line), ft_lstclear(&head, free), FALSE);
		if (!is_start)
			free(line);
	}
	if (!is_start)
	{
		print_error("Map: no map found.");
		ft_lstclear(&head, free);
		return (FALSE);
	}
	if (!list_to_map(head, conf))
		return (ft_lstclear(&head, free), FALSE);
	ft_lstclear(&head, free_node_only);
	return (TRUE);
}
