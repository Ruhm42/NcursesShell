/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 13:58:12 by rda-cost          #+#    #+#             */
/*   Updated: 2015/05/30 17:57:53 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"
#include <time.h>

int		nc_delete(t_ncurses *nc)
{
	endwin();
	(void)nc;
	return (0);
}

void	nc_getprompt(t_ncurses *nc)
{
	time_t			t;
	struct tm		now;
	const char		fmt[] = "[%X] > ";

	t = time(0);
	now = *localtime(&t);
	memset(nc->prompt, 0, sizeof(nc->prompt));
	strftime(nc->prompt, sizeof(nc->prompt) - 1, fmt, &now);
}

void	nc_carriage_return(t_ncurses *nc)
{
	getyx(nc->win, nc->coord.y, nc->coord.x);
	if (nc->coord.x > 0)
		wmove(nc->win, nc->coord.y + 1, 0);
}

void	ctn_del(t_ctn *ptr)
{
	if (!ptr)
		return ;
	while (ptr->next)
	{
		if (ptr->prev)
			free(ptr->prev);
		ptr = ptr->next;
	}
	if (ptr->prev)
		free(ptr->prev);
	free(ptr);
}

void	str_clear(t_str *str)
{
	t_ctn	*ptr;

	ptr = str->cur;
	ctn_del(ptr);
	memset(str, 0, sizeof(t_str));
}
