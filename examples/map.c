/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 00:39:57 by ablin             #+#    #+#             */
/*   Updated: 2018/01/27 01:08:53 by ablin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** sets the first map as small as possible
** we use ft_min + the nb of tetri to determine the smallest size
*/

char	**ft_set(int size)
{
	char	**map;
	int		line;
	int		col;

	if ((map = (char **)malloc(sizeof(char *) * (size + 1))) == NULL)
		return (0);
	line = 0;
	while (line < size)
	{
		col = 0;
		map[line] = ft_strnew(size + 1);
		while (col < size)
		{
			map[line][col] = '.';
			col++;
		}
		map[line][col] = '\n';
		map[line][col + 1] = '\0';
		line++;
	}
	map[line] = NULL;
	return (map);
}

/*
** ft_map expands an existing map by 1 ( +1 col and line) and free the old map
** called in ft_fit if the tetriminos couldnt fit
*/

char	**ft_map(char **map, int size)
{
	t_newmap	new;

	if ((new.newmap = (char **)malloc(sizeof(char *) * (size + 2))) == NULL)
		return (0);
	new.line = 0;
	while (map[new.line] != NULL)
	{
		new.col = -1;
		new.newmap[new.line] = ft_strnew(size + 2);
		while (map[new.line][++new.col] != '\n')
			new.newmap[new.line][new.col] = map[new.line][new.col];
		new.newmap[new.line][new.col] = '.';
		new.newmap[new.line][new.col + 1] = '\n';
		new.newmap[new.line++][new.col + 2] = '\0';
	}
	new.col = -1;
	new.newmap[new.line] = ft_strnew(size + 1);
	while (new.col++ < size)
		new.newmap[new.line][new.col] = '.';
	new.newmap[new.line][new.col] = '\n';
	new.newmap[new.line][new.col + 1] = '\0';
	new.newmap[new.line + 1] = NULL;
	free(map);
	map = NULL;
	return (new.newmap);
}

/*
** insert the tetriminos (board) in the map
** called in ft_checkpos
*/

char	**ft_insert(char **map, t_tetri *tetri, int line, int col)
{
	int		count;
	t_pos	pos;

	pos = ft_pos(tetri->board);
	count = 0;
	while (count < 4)
	{
		map[line + pos.x[count]][col + pos.y[count]] = tetri->letter;
		count++;
	}
	return (map);
}

/*
** this function prints the final map
*/

void	ft_showtab(char **board)
{
	int i;
	int j;

	i = 0;
	if (board == NULL)
		return ;
	while (board[i] != NULL)
	{
		j = 0;
		while (board[i][j] != '\0')
		{
			ft_putchar(board[i][j]);
			j++;
		}
		i++;
	}
}

/*
** this ft erase a specific tetriminos from the map
*/

char	**ft_erase(char **map, char letter)
{
	int	line;
	int col;

	line = 0;
	while (map[line] != NULL)
	{
		col = 0;
		while (map[line][col] != '\n')
		{
			if (map[line][col] == letter)
				map[line][col] = '.';
			col++;
		}
		line++;
	}
	return (map);
}
