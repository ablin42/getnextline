/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 02:36:20 by ablin             #+#    #+#             */
/*   Updated: 2018/02/21 02:50:36 by ablin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*concatenate(t_gnl gnl, char *str)
{
	int		i;
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
	str = ft_strnew(gnl.size);////
	j = ft_strlen(gnl.remain);
	while (gnl.remain[i] != '\0' && i < (int)j) // remain[i] != '\n' // '\0'
	{
		str[i] = gnl.remain[i];
		i++;
	//	ft_putstr(ft_itoa(i));
	}
	j = 0;
	while (tmp != NULL && tmp[i] != '\0')
	{
		str[i] = tmp[i];//
		i++;
		//j++;
	}
//	j = 0;
	while (i < gnl.size && gnl.buf[j] != '\n')
		str[i++] = gnl.buf[j++];
	str[i] = '\0';
	if (tmp != NULL) /////jen suis la xddd
		free(tmp);
	return (str);
}

t_gnl	treat(t_gnl gnl, int fd)//
{
	//char	*str;

	gnl.tmpline = NULL;
	gnl.i = 0;
	gnl.size = ft_strlen(gnl.remain);
	/*if (gnl.remain != NULL)
	{
		gnl.size = ft_strlen(gnl.remain);
		tmp2 = ft_strnew(gnl.size);
		*line = concatenate(gnl.remain, NULL, ft_strlen(gnl.remain), tmp2);
		printf("[final line = %s]\n", *line);
		free(tmp2);
	}*/
	
	if (gnl.remain != NULL && ft_strchr(gnl.remain, '\n') != 0)
	{
		while (gnl.remain[gnl.i] != '\n')
			gnl.i++;
		gnl.tmpline = ft_strnew(gnl.i);
		gnl.i = 0;
		while (gnl.remain[gnl.i] != '\n')
		{
			gnl.tmpline[gnl.i] = gnl.remain[gnl.i];
			gnl.i++;
		}
		gnl.size = -1;
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
	return (gnl);
}

int		get_next_line(const int fd, char **line)
{
	static	t_gnl	gnl;

//	gnl.rd = 0;
	if (BUFF_SIZE < 1 || fd < 0 || line == NULL)
		return (-1);
	if (gnl.remain == NULL)
		gnl.remain = ft_strnew(BUFF_SIZE);//allouer en static comme le buffer?
	ft_memset(gnl.buf, '\0', BUFF_SIZE);
	gnl = treat(gnl, fd); //*line
	if (gnl.tmpline != NULL)//
		*line = ft_strdup(gnl.tmpline);
	if (gnl.rd < 0)
		return (-1);
	if ((ft_strcmp(gnl.remain, "") == 0 && gnl.size == 0))
		return (0);
	if (gnl.size != -1)
		gnl.remain = ft_strcpy(gnl.remain, gnl.buf);
	if (ft_strchr(gnl.remain, '\n') != 0)
	{
		gnl.remain = ft_strchr(gnl.remain, '\n');
		gnl.remain++;
	}
	else
		gnl.remain = NULL;
	return (1);
}
/*
int		main(int argc, char **argv)
{
	int		fd;
	//int		fd2;
	int		ret;
	char	*line;

	(void)argc;
	line = NULL;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		printf("%s\n", line);
		if (ret == 0)
			break;
	}
	return (0);
}*/
