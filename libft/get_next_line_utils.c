/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:50:51 by brpereir          #+#    #+#             */
/*   Updated: 2024/09/19 13:30:26 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strchr_l(const char *str)
{
	size_t	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '\n')
			return (1);
	}
	return (0);
}

char	*check_new_line(char *line)
{
	if (line[0] == '\0')
	{
		free(line);
		line = 0;
	}
	return (line);
}

char	*join_string(char *s1, char *s2)
{
	char	*ret;
	char	*p;
	int		i;
	int		j;
	int		size;

	size = ft_strlen(s2);
	if (s1)
		size += ft_strlen(s1);
	p = (char *)malloc(sizeof(*p) * (size + 1));
	if (!p)
		return (NULL);
	ret = p;
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		p[i++] = s2[j++];
	p[i] = 0;
	free(s1);
	return (ret);
}
