/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_remember.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 10:51:32 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/01 16:07:57 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

static void		pull_ctn(t_rmb **hist, t_str *str, char *concat)
{
	t_ctn			*ptr;
	unsigned int	i;

	i = 0;
	ptr = str->cur;
	while (ptr)
	{
		concat[i++] = ptr->c;
		ptr = ptr->next;
	}
	nc_add_history(hist, str->cur);
	str->cur = NULL;
	memset(str, 0, sizeof(t_str));
}

static void		rmb_insert(t_rmb **lst, t_rmb *n)
{
	t_rmb			*ptr;

	if (!*lst)
		*lst = n;
	else
	{
		ptr = *lst;
		while ((*lst)->next)
			(*lst) = (*lst)->next;
		(*lst)->next = n;
		n->prev = *lst;
		*lst = ptr;
	}
}

char			*rmb_create(t_rmb **lst, t_rmb **hist,
	t_str *cur, char prompt[PROMPT_SZ])
{
	t_rmb			*n;
	char			*ret;
	unsigned int	sz;

	sz = strlen(prompt) + cur->sz + 1;
	if (!(n = malloc(sizeof(t_rmb))))
		return (NULL);
	memset(n, 0, sizeof(t_rmb));
	if (!(n->str = malloc(sizeof(char) * sz)))
		return (NULL);
	if (!(ret = malloc(sizeof(char) * (cur->sz + 1))))
		return (NULL);
	memset(n->str, 0, sizeof(char) * sz);
	memset(ret, 0, sizeof(char) * (cur->sz + 1));
	strcat(n->str, prompt);
	pull_ctn(hist, cur, ret);
	strcat(n->str, ret);
	rmb_insert(lst, n);
	return (ret);
}

void			rmb_add(t_rmb **lst, char *ins)
{
	t_rmb			*n;

	if (!(n = malloc(sizeof(t_rmb))))
		return ;
	memset(n, 0, sizeof(t_rmb));
	if (!(n->str = strdup(ins)))
		return ;
	rmb_insert(lst, n);
}
