/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 13:51:03 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/05 15:59:00 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>

enum	e_map_ret
{
	MAP_OK,
	MAP_FULL,
	MAP_EXIST,
	MAP_ERROR,
	MAP_RET_SZ,
};

typedef	char		t_key;
typedef	char		t_val;

typedef struct		s_methods
{
	size_t			(*hash)(t_key *);
	t_key			*(*dup_key)(const t_key *);
	t_val			*(*dup_val)(const t_val *);
	int				(*cmp_key)(const t_key *, const t_key *);
	int				(*cmp_val)(const t_val *, const t_val *);
	void			(*del_key)(t_key **);
	void			(*del_val)(t_val **);
}					t_methods;

typedef struct		s_cell
{
	t_key			*key;
	t_val			*val;
}					t_cell;

typedef struct		s_map
{
	size_t			sz;
	size_t			cur_sz;
	t_cell			*data;
	t_methods		methods;
}					t_map;

size_t				hash_get_index(t_map *map, t_key *key);
void				hash_create(t_map *map, unsigned int sz);
int					hash_put(t_map *map, t_key *key, t_val *val);
void				hash_rehash(t_map *map);
t_val				*hash_get(t_map *map, t_key *key);
void				hash_del(t_map *map, t_key *key);
void				hash_update(t_map *map, t_key *key, t_val *val);

/*
**	utils
*/

bool				cell_is_free(t_cell *cell);
void				cell_delete(t_map *map, t_cell *cell);
void				hash_print(t_map *map);

/*
**	Hash str
*/

void				hash_create_str_str(t_map *map, unsigned int sz);
size_t				hash_basic_string(char *s);

#endif
