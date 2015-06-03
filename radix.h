/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 10:07:17 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/02 18:27:05 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RADIX_H
# define RADIX_H

# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# include "gnl.h"

typedef struct		s_rdx
{
	char			*str;
	bool			st;
	struct s_rdx	*next;
	struct s_rdx	*prev;
	struct s_rdx	*down;
}					t_rdx;

typedef struct		s_wrap
{
	char			*str;
	struct s_wrap	*next;
	struct s_wrap	*prev;
}					t_wrap;

typedef struct		s_search
{
	t_rdx			*tree;
	t_wrap			*start;
	t_wrap			*cur;
	char			*target;
	char			*prefix;
}					t_search;

/*
**	radix fonctions
*/

t_rdx				*new_node(char *str);
void				radix_insert(t_rdx **root, char *str);
void				rdx_call_back(t_search *s, t_rdx *n, char *str, char *pfx);

/*
**	wrap fonctions
*/

void				wrap_build(t_wrap **start, t_wrap **cur, char *str);
void				wrap_free(t_wrap **start, t_wrap **cur);

/*
**	search fonctions
*/

void				rdx_search(t_search *search, char *target);
char				*rdx_find_prefix(t_rdx *root, char *string);

/*
**	utility fonctions
*/

void				print_wrap(t_wrap *start);
void				radix_print(t_rdx *root, char *cur);
void				radix_from_file(t_rdx **root, char *file);

/*
**	extension fonctionss
*/

char				*join_free(char *start, char *rec);
char				*join_safe(char *s1, char *s2);
char				*strjoin(char const *s1, char const *s2);
int					min_strncmp(char *s1, char *s2, unsigned int *out);

#endif
