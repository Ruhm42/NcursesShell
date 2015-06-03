/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_str_extract.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 10:19:23 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/03 15:11:09 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

static void		str_end_import(t_str *str, char *n, t_ctn *end, t_ctn *save)
{
	if (!n)
		return ;
	if (end)
		end->prev = save;
	if (save)
		save->next = end;
	(void)str;
}

void			ncurses_str_import(t_str *str, char *n, t_ctn *end,
	unsigned int *sz)
{
	t_ctn			*tmp;
	t_ctn			*save;

	*sz = 0;
	while (n && n[*sz])
	{
		if (!(tmp = malloc(sizeof(t_ctn))))
			return ;
		memset(tmp, 0, sizeof(t_ctn));
		tmp->c = n[*sz];
		if (!str->cur)
			str->cur = tmp;
		else
		{
			save->next = tmp;
			tmp->prev = save;
		}
		save = tmp;
		(*sz)++;
	}
	str_end_import(str, n, end, save);
	str->pos = *sz;
	str->sz += *sz;
}

void			reset_extracted_str(t_str *str, t_ctn *end, unsigned int sz)
{
	if (end && end->prev)
		end->prev->next = NULL;
	ctn_del(str->cur);
	str->cur = NULL;
	str->sz -= sz;
}

char			*ncurses_str_extract(t_str *str, t_ctn **end, unsigned int *sz)
{
	char			*ret;
	t_ctn			*iterator;

	*sz = 0;
	ret = malloc(sizeof(char) * (str->pos_tab + 1));
	memset(ret, 0, sizeof(char) * (str->pos_tab + 1));
	iterator = str->cur;
	while (iterator)
	{
		if (*sz >= str->pos_tab || (iterator->c == ' ' && !(*sz = 0)))
			break ;
		ret[*sz] = iterator->c;
		(*sz) += 1;
		iterator = iterator->next;
	}
	ret[*sz] = 0;
	if (*sz == 0 || str->pos_tab > *sz)
	{
		free(ret);
		return (NULL);
	}
	*end = iterator;
	return (ret);
}
