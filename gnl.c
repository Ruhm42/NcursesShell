/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 10:29:40 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/02 11:11:10 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static char		*set_rest(char *str)
{
	while (*str != '\n' && *str != '\0')
		str++;
	if (*str == '\n' && str[1] != '\0')
		return (strdup(++str));
	else
		return (NULL);
}

static void		add_str(char **line, char *str)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	if (*line)
	{
		tmp = strdup(*line);
		free(*line);
		len = strlen(tmp) + strlen(str);
		*line = (char *)malloc(sizeof(char) * (len + 1));
		strcpy(*line, tmp);
		free(tmp);
		while ((*line)[i])
			i++;
	}
	else
	{
		len = strlen(str);
		*line = (char *)malloc(sizeof(char) * (len + 1));
	}
	while (*str != '\0' && *str != '\n')
		(*line)[i++] = *str++;
	(*line)[i] = '\0';
}

static int		init_with_rest(char **line, char **rest)
{
	char	*del;

	if (*rest && strchr(*rest, '\n'))
	{
		add_str(line, *rest);
		del = *rest;
		*rest = set_rest(del);
		free(del);
		return (1);
	}
	else if (*rest && !strchr(*rest, '\n'))
	{
		*line = strdup(*rest);
		free(*rest);
		*rest = NULL;
	}
	return (0);
}

static int		start(char **line, char **rest, int const fd)
{
	if (BUFF_SIZE <= 0 || fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	if (init_with_rest(line, rest))
		return (1);
	return (0);
}

int				gnl(int const fd, char **line)
{
	int				check;
	int				ret;
	char			*str;
	static char		*rest = NULL;

	check = start(line, &rest, fd);
	if (check != 0)
		return (check);
	str = malloc(sizeof(char) * BUFF_SIZE);
	memset(str, 0, sizeof(char) * BUFF_SIZE);
	while ((ret = read(fd, str, BUFF_SIZE)) > 0 && !strchr(str, '\n'))
	{
		add_str(line, str);
		bzero(str, BUFF_SIZE + 1);
	}
	if (ret > 0)
	{
		str[ret] = '\0';
		add_str(line, str);
		rest = set_rest(str);
	}
	free(str);
	if (ret > 1)
		ret = 1;
	return (ret);
}
