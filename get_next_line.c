/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 02:36:20 by ablin             #+#    #+#             */
/*   Updated: 2018/03/16 01:05:47 by ablin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

char	*concatenate(t_gnl gnl, char *str)
{
	int			i;
	size_t		j;
	char		*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	if (str != NULL)
	{
		tmp = ft_strdup(str);
		ft_strdel(&str);
	}
	str = ft_strnew(gnl.size * 2);
	if (gnl.remain != NULL)
		str = ft_strcat(str, gnl.remain);
	if (tmp != NULL)
		str = ft_strcat(str, tmp);
	i = ft_strlen(str);
	while (i < gnl.size && gnl.buf[j] != '\n')
		str[i++] = gnl.buf[j++];
	str[i] = '\0';
	if (tmp != NULL)
		ft_strdel(&tmp);
	return (str);
}

t_gnl	read_line(t_gnl gnl, int fd)
{
	gnl.i = 0;
	gnl.size = ft_strlen(gnl.remain);
	if (gnl.remain != NULL && ft_strchr(gnl.remain, '\n') != 0)
	{
		while (gnl.remain[gnl.i] != '\n')
			gnl.i++;
		gnl.tmpline = ft_strnew(gnl.i);
		ft_strncpy(gnl.tmpline, gnl.remain, gnl.i);
		return (gnl);
	}
	while ((gnl.rd = read(fd, gnl.buf, BUFF_SIZE)) >= 0)
	{
		gnl.i = 0;
		gnl.buf[gnl.rd] = '\0';
		while (gnl.i < gnl.rd && gnl.buf[gnl.i - 1] != '\n')
			gnl.i++;
		gnl.size += gnl.i;
		gnl.tmpline = concatenate(gnl, gnl.tmpline);
		ft_strclr(gnl.remain);
		if (ft_strchr(gnl.buf, '\n') != 0 || gnl.rd < BUFF_SIZE)
			break ;
	}
	gnl.remain = ft_strcpy(gnl.remain, gnl.buf);
	return (gnl);
}

int		get_next_line(const int fd, char **line)
{
	static	t_gnl	gnl;

	if (BUFF_SIZE < 1 || fd < 0 || line == NULL)
		return (-1);
	gnl.tmpline = NULL;
	if (gnl.remain == NULL)
		gnl.remain = ft_strnew(BUFF_SIZE * 2);
	gnl = read_line(gnl, fd);
	if (gnl.tmpline != NULL)
		*line = ft_strdup(gnl.tmpline);
	if (gnl.rd < 0)
		return (-1);
	if ((ft_strcmp(gnl.remain, "") == 0 && gnl.size == 0))
		return (0);
	if ((gnl.remain = ft_strchr(gnl.remain, '\n')) != 0)
	{
		gnl.remain++;
	}
	else
		gnl.remain = NULL;
	return (1);
}
/*/
int		main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	*line;

	(void)argc;
	line = NULL;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		printf("%d[%s]\n", ret, line);
		if (ret == 0)
			break;
	}
	return (0);
}//*/
