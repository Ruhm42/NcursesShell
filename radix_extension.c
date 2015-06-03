/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 17:56:20 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/03 13:51:39 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix.h"

char	*strjoin(char const *s1, char const *s2)
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

int		min_strncmp(char *s1, char *s2, unsigned int *out)
{
	unsigned int	sz1;
	unsigned int	sz2;

	sz1 = strlen(s1);
	sz2 = strlen(s2);
	if (sz1 > sz2)
	{
		if (out)
			*out = sz2;
		return (strncmp(s1, s2, sz2));
	}
	else
	{
		if (out)
			*out = sz1;
		return (strncmp(s1, s2, sz1));
	}
}

char	*join_free(char *start, char *rec)
{
	char	*ret;

	if (!rec)
	{
		return (NULL);
	}
	if (!start)
		return (strdup(rec));
	ret = strjoin(start, rec);
	free(rec);
	return (ret);
}

char	*join_safe(char *s1, char *s2)
{
	char	*ret;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (strdup(s2));
	if (!s2)
		return (strdup(s1));
	ret = strjoin(s1, s2);
	return (ret);
}
