/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 08:27:18 by ablin             #+#    #+#             */
/*   Updated: 2018/01/27 01:05:45 by ablin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FILLIT_H
# define __FILLIT_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include "../lib/libft.h"

typedef	struct		s_tetri
{
	char			**board;
	char			letter;
	int				x;
	int				y;
	struct s_tetri	*next;
	struct s_tetri	*prev;
	struct s_tetri	*start;
}					t_tetri;

typedef	struct		s_double
{
	t_tetri			*tail;
	t_tetri			*head;
}					t_double;

typedef	struct		s_pos
{
	int				x[4];
	int				y[4];
}					t_pos;

typedef	struct		s_fit
{
	int				line;
	int				col;
	int				count;
}					t_fit;

typedef	struct		s_file
{
	int				fd;
	int				rd;
	int				tnb;
	int				end;
	char			buf[21];
}					t_file;

typedef	struct		s_newmap
{
	char			**newmap;
	int				line;
	int				col;
}					t_newmap;

typedef	struct		s_move
{
	int				i;
	int				l;
	int				hashtag_count;
	int				mv_up;
	int				mv_l;
	int				n;
	int				k[4];
	char			**tmp;
}					t_move;

int					ft_lsttetri(t_double *lst, char **board, int tnb);
t_pos				ft_pos(char **board);
void				ft_tetripos(t_tetri *tetri, int size);
void				ft_showtab(char **board);
char				**ft_solve(t_tetri *tetri, char **map, int size, int tnb);
char				**ft_board(char *str);
char				**malloc_it(void);
char				**ft_swap_up(char **board, int line, int i, int mv_up);
char				**ft_left(char **board);
char				**ft_united(char **board);
char				**ft_map(char **map, int size);
char				**ft_set(int size);
char				**ft_insert(char **map, t_tetri *tetri, int line, int col);
char				**ft_erase(char **map, char letter);
int					ft_fit(t_tetri *tetri, t_pos pos, int size, char **nmap);
int					ft_check(char *str);
int					ft_min(int tetrinb);
int					ft_read(char *filename);
int					first_left(char **board);
int					ft_checkpos(t_tetri *tetri, char **map, int size);

#endif
