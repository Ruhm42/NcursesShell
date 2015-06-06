/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_str_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 10:34:23 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/05 16:00:06 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

void	hash_del_str(char **k)
{
	if (!*k)
		return ;
	free(*k);
	*k = NULL;
}

size_t	hash_basic_string(char *s)
{
	size_t	hash;

	hash = 0;
	while (s && *s)
		hash = *s++ + (hash << 6) + (hash << 16) - hash;
	return (hash);
}

size_t	hash_fnv1a_string(char *s)
{
	size_t	hash;

	hash = 2166136261;
	while (s && *s)
		hash = (*s++ ^ hash) * 16777619;
	return (hash);
}

void	hash_create_str_str(t_map *map, unsigned int sz)
{
	memset(map, 0, sizeof(t_map));
	map->methods.hash = &hash_fnv1a_string;
	map->methods.dup_key = &strdup;
	map->methods.dup_val = &strdup;
	map->methods.cmp_key = &strcmp;
	map->methods.cmp_val = &strcmp;
	map->methods.del_key = &hash_del_str;
	map->methods.del_val = &hash_del_str;
	hash_create(map, sz);
}
