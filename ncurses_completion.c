/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_completion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 15:18:39 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/01 18:50:55 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

static bool	node_is_valid(t_rdx *root, char *str, int *cur, int *index)
{
	while (str[*cur] && root->str[*index] && str[*cur] == root->str[*index])
	{
		*cur += 1;
		*index += 1;
	}
	if (!str[*cur] || !root->str[*index])
		return (true);
	return (false);
}

static t_rdx	*find_next_node(t_rdx *root, char *substr, char *str, int *cur)
{
	int		save;
	int		index;

	save = *cur;
	while (root)
	{
		*cur = save;
		index = 0;
		if (save < (signed)strlen(substr))
		{
			if (node_is_valid(root, substr, cur, &index))
				return (root->down);
		}
		else
		{
			if (strncmp(str + *cur, root->str, strlen(root->str)) >= 0)
				return (root->down);
		}
		root = root->next;
	}
	return (NULL);
}

// static void		ctn_to_string(t_str *ptr, char *substr, char *str)
// {
// 	t_ctn	*tmp;
// 	int		index;
// 	int		sz;

// 	sz = 0;
// 	if (str[0])
// 		sz = strlen(str);
// 	index = 0;
// 	tmp = ptr->cur;
// 	while (tmp)
// 	{
// 		substr[index] = tmp->c;
// 		str[index] = tmp->c;
// 		tmp = tmp->next;
// 		index++;
// 	}
// 	if ((unsigned)index > ptr->pos_tab)
// 	{
// 		if (sz)
// 			str[sz] = 0;
// 		else
// 			str[ptr->pos_tab + 1] = 0;
// 	}
// 	else
// 		str[index] = 0;
// 	substr[ptr->pos_tab] = 0;
// }

static void		ctn_to_string(t_str *ptr, char *str)
{
	t_ctn	*tmp;
	int		index;

	index = 0;
	tmp = ptr->cur;
	while (tmp)
	{
		str[index] = tmp->c;
		tmp = tmp->next;
		index++;
	}
	str[index] = 0;
}

static void	concat_str(t_str *str, t_rdx *node)
{
	int	i;

	if (!node->str)
		return ;
	i = -1;
	while (node->str[++i])
		ctn_create(str, node->str[i]);
}

static void	ncurses_completion(t_str *old, t_str next, t_rdx *root, t_ncurses *tmp)
{
	char			substr[old->sz];
	static char		*str = NULL;
	t_ctn			*save;
	int				index;

	if (!str)
	{
		str = malloc(sizeof(char) * (old->sz + 1));
		memset(str, 0, old->sz + 1);
		ctn_to_string(old, str);
	}
	ctn_to_string(old, substr);
	//printf("pos = %d sub = %s str = %s\n", old->pos_tab, substr, str);
	index = 0;
	save = old->cur;
	old->sz = 0;
	old->pos = 0;
	old->cur = NULL;
	while (root)
	{
		//printf("str = %s\n", root->str);
		concat_str(old, root);
		if (root->st && old->sz >= strlen(str))
		{
			str = strjoin(str, root->str);
			break ;
		}
		root = find_next_node(root, substr, str, &index);
	}
	if (old->sz < next.sz)
	{
		ctn_del(old->cur);
		old->cur = save;
		old->sz = next.sz;
		old->pos = next.pos;
	}
	else
		ctn_del(save);
	nc_add(tmp, substr);
}

void	nc_tab(void *arg)
{
	t_ncurses	*nc;

	nc = arg;
	if (!nc->tree || !nc->tree->down)
		return ;
	//endwin();
	//printf("pos = %d\n", nc->str.pos_tab);
	if (!nc->str.pos_tab)
		nc->str.pos_tab = nc->str.pos;
	//printf("pos = %d\n", nc->str.pos_tab);
	ncurses_completion(&(nc->str), nc->str, nc->tree->down, nc);
	//printf("----\n");
	//radix_print(nc->tree, NULL);
	//exit(1);

}
