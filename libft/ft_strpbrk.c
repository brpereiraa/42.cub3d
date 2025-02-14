/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpereir <brpereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:45:07 by brpereir          #+#    #+#             */
/*   Updated: 2025/02/14 12:25:23 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *s, const char *accept) 
{
	const char *a;

	while (*s)
	{
		a = accept;
		while(*a)
		{
			if (*s == *a)
				return ((char *)s);
			a++;
		}
		s++;
	}
	return (NULL);
}

char	*ft_strpbrk_skip(const char *s, const char *accept)
{
    char *ptr;

	ptr = ft_strpbrk(s, accept);
    while (ptr && *ptr && ft_strchr(accept, *ptr))
        ptr++;
    return ptr;
}