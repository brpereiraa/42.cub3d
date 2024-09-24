/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:50:56 by brpereir          #+#    #+#             */
/*   Updated: 2024/09/19 11:45:16 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_decimal(int c)
{
	char	*temp;
	size_t	size;

	if (!c)
		return (write(1, "0", 1));
	temp = ft_itoa (c);
	ft_putstr_fd (temp, 1);
	size = ft_strlen(temp);
	free(temp);
	return (size);
}
