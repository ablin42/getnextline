/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 02:36:29 by ablin             #+#    #+#             */
/*   Updated: 2018/03/22 21:46:44 by ablin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"

# define BUFF_SIZE 10000

typedef	struct	s_get
{
	char	buf[BUFF_SIZE + 1];
	char	*remain;
	char	*tmpline;
	int		rd;
	int		size;
	int		i;
}				t_get;

typedef	struct	s_gnl
{
	char	buf[BUFF_SIZE + 1];
	int		rd;
	int		size;
	int		i;
}				t_gnl;

typedef	struct	s_lst
{
	int				fd;
	char			*str;
	struct	s_lst	*start;
	struct	s_lst	*next;
}				t_lst;

t_gnl			read_line(t_gnl gnl, int fd);
char			*concatenate(t_gnl gnl, char *str);
int				get_next_line(const int fd, char **line);
char			*ft_strjoinfree(const char *s1, const char *s2);
t_lst			*fetch_fd(t_lst **lst, int fd);
t_lst			*add_list(t_lst *lst, int fd);
char			*save_remain(char *str);
#endif
