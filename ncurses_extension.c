/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_extension.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 14:50:37 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/06 15:20:12 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

void	line_to_kvp(t_ncurses *nc, char *line)
{
	int	index;

	index = -1;
	while (line[++index])
		if (line[index] == ' ')
			break ;
	if (!index || !line[index])
		return ;
	line[index] = 0;
	init_kvp(nc, line, line + index + 1);
}

void	ncurses_conf_from_file(t_ncurses *nc, char *file)
{
	int		fd;
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		return ;
	line = NULL;
	hash_create_str_str((&nc->map), 100);
	while (gnl(fd, &line))
	{
		line_to_kvp(nc, line);
		if (line)
			free(line);
	}
	if (line)
	{
		line_to_kvp(nc, line);
		free(line);
	}
	close(fd);
}
