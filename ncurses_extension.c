/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_extension.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 14:50:37 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/01 14:52:23 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

char		*strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	i;
	size_t	j;

	i = strlen(s1) + strlen(s2);
	if (!(r = malloc(sizeof(*r) * (i + 1))))
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		r[i++] = s2[j++];
	r[i] = 0;
	return (r);
}

void	radix_print(t_rdx *root, char *cur)
{
	if (!root)
		return ;
	while (root)
	{
		printf("str = %s\n", root->str);
		if (root->st)
		{
			if (cur)
				printf("%s\n", strjoin(cur, root->str));
			else
				printf("%s\n", root->str);
		}
		if (cur)
			radix_print(root->down, strjoin(cur, root->str));
		else
			radix_print(root->down, root->str);
		root = root->next;
	}
}