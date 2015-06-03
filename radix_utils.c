/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 10:10:38 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/03 15:08:31 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix.h"
#include <sys/stat.h>
#include <fcntl.h>

void		print_wrap(t_wrap *start)
{
	t_wrap	*save;

	if (!(save = start))
		return ;
	if (save->next == save)
		return (void)(printf("%s\n", save->str));
	while (start)
	{
		printf("%s\n", start->str);
		if (start->next == save)
			return ;
		start = start->next;
	}
}

void		radix_print(t_rdx *root, char *cur)
{
	char	*concat;

	(void)cur;
	if (!root)
		return ;
	while (root)
	{
		concat = NULL;
		if (cur)
			concat = strjoin(cur, root->str);
		if (root->st)
		{
			if (concat)
				printf("%s\n", concat);
			else
				printf("%s\n", root->str);
		}
		if (concat)
			radix_print(root->down, concat);
		else
			radix_print(root->down, root->str);
		if (concat)
			free(concat);
		root = root->next;
	}
}

void		radix_from_file(t_rdx **root, char *file)
{
	int		fd;
	char	*line;
	size_t	ct;

	if ((fd = open(file, O_RDONLY)) == -1)
		return ;
	ct = 0;
	while (gnl(fd, &line))
	{
		radix_insert(root, line);
		if (line)
			free(line);
		ct++;
	}
	if (line)
	{
		ct++;
		radix_insert(root, line);
		free(line);
	}
	close(fd);
}
