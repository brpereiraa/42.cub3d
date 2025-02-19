/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 01:56:10 by marvin            #+#    #+#             */
/*   Updated: 2024/09/19 13:15:16 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_len(unsigned int c)
{
	int	len;

	len = 0;
	while (c)
	{
		len++;
		c /= 16;
	}
	return (len);
}

static void	print(unsigned int c, char casing)
{
	if (c >= 16)
	{
		print(c / 16, casing);
		print(c % 16, casing);
	}
	else
	{
		if (c < 10)
			ft_putchar_fd((c + 48), 1);
		else
		{
			if (casing == 'a')
				ft_putchar_fd((c - 10 + 'a'), 1);
			else if (casing == 'A')
				ft_putchar_fd((c - 10 + 'A'), 1);
		}
	}
}

int	ft_print_hex(unsigned int c, char casing)
{
	if (c == 0)
		return (write(1, "0", 1));
	print(c, casing);
	return (print_len(c));
}
