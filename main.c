/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 13:50:28 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/01 16:50:19 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

#define LOG "log.txt"
#include <fcntl.h>
#include <unistd.h>
#define MOD  S_IRUSR | S_IWUSR |S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH

void	log_txt(char *lg)
{
	int				fd;
	const mode_t	mode = MOD;

	fd = open(LOG, O_RDWR | O_CREAT | O_APPEND, mode);
	write(fd, lg, strlen(lg));
	write(fd, "\n", 1);
	close(fd);
}

/*
**	nc_start open a new ncurses window
**	nc_loop handles input, history, and line-edition
**	(char *) nc.input is freed at each start of loop
**	you have to duplicate it if you want keep it in memory
**	To add something in the shell, use nc_add
**	nc_end only calls endwin()
*/

int		main(void)
{
	t_ncurses	nc;

	if (!nc_start(&nc))
		return (nc_delete(&nc));
	radix_insert(&(nc.tree), strdup("test"));
	radix_insert(&(nc.tree), strdup("teste"));
	radix_insert(&(nc.tree), strdup("testasqqew"));
	radix_insert(&(nc.tree), strdup("testasq"));
	radix_insert(&(nc.tree), strdup("testasqqewtest"));
	radix_insert(&(nc.tree), strdup("testasqqewte"));
	while (!nc.stopped)
	{
		nc_loop(&nc);
		if (nc.input != NULL)
		{
			log_txt(nc.input);
			nc_add(&nc, nc.input);
		}
	}
	return (nc_delete(&nc));
}
