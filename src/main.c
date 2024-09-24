/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:10 by bruno             #+#    #+#             */
/*   Updated: 2024/09/24 17:29:12 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void print_error(char *msg, int exit_code)
{
	ft_printf("%s", msg);
	exit(exit_code);
}

int main(int ac, char **av)
{
	if(ac != 2)
		print_error("invalid number of arguments", 0);
	if(file_validation(av[1]))
		print_error("invalid file name", 0);
	map_validation(av[1]);
	
	return(0);
}