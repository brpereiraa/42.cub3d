/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:51:05 by brpereir          #+#    #+#             */
/*   Updated: 2024/09/19 13:31:24 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*clean_line(char *str)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	if (!str[0])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		temp[j] = str[j];
		j++;
	}
	temp[i] = '\0';
	return (temp);
}

static char	*str_rest(char *str)
{
	size_t	i;
	char	*temp;
	char	*start;

	if (!*str)
	{
		free(str);
		return (NULL);
	}
	start = str;
	while (*str && *str != '\n')
		str++;
	if (*str == '\n')
		str++;
	i = 0;
	while (str[i] && str)
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 1));
	temp[i] = 0;
	while (i-- > 0)
		temp[i] = str[i];
	free(start);
	return (temp);
}

static char	*get_text(char *str, int fd)
{
	char	*temp;
	int		nbytes;

	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	nbytes = 1;
	while (nbytes > 0 && !ft_strchr_l(str))
	{
		nbytes = read(fd, temp, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free (temp);
			free (str);
			return (NULL);
		}
		temp[nbytes] = 0;
		str = join_string(str, temp);
	}
	free(temp);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd == -1)
		free(str);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = get_text(str, fd);
	if (!str)
		return (NULL);
	line = clean_line(str);
	str = str_rest(str);
	return (line);
}

// int main(void)
// {
// 	int	fd;

// 	fd = open("a.txt", O_RDONLY);
// 	printf("%s\n", get_next_line(fd));
// 	return (0);
// }
