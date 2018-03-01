/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 02:36:29 by ablin             #+#    #+#             */
/*   Updated: 2018/02/21 02:45:29 by ablin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GET_NEXT_LINE_H
# define __GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include "Libft/libft.h"

# define BUFF_SIZE 35

typedef	struct	s_gnl
{
	char	*remain;
	char	buf[BUFF_SIZE + 1];
	char	*tmpline;
	int		rd;
	int		size;
	int		i;
}				t_gnl;

int		get_next_line(const int fd, char **line);
#endif
