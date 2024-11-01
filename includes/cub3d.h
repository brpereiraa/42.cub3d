/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:37:58 by bruno             #+#    #+#             */
/*   Updated: 2024/11/01 18:06:37 by brpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_game t_game;
typedef struct s_player t_player;

struct s_game {
	t_game	*player;
	char	**map;
	void	*mlx;
	void	*win;
};

struct s_player { 
	int	pos_x;
	int	pos_y;
};

/*.........map.c..............*/

int	map_init(t_game *game, char *file);
char	**map_read(char *file);
int	map_lines(char *file);

/*..............................*/

int	file_validation(char *map);
int	char_validation(char *map);
int	map_validation(char *map);

#endif

