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

char	*concatenate(char *line, char *buf, int size, char *tmp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (line != NULL)
	{
		while (i < ft_strlen(line))
		{
			tmp[i] = line[i];
			i++;
		}
	}
	while (i < (size_t)size && buf[j] != '\n')
	{
		tmp[i] = buf[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int		use_remain(char **line, char *remain)
{
	int		i;
	int		size;
	char	*tmp;

	i = 0;
	size = 0;
	if (remain != NULL)
	{
		size = ft_strlen(remain);
		tmp = ft_strnew(size);
		*line = concatenate(remain, NULL, ft_strlen(remain), tmp);
		printf("[final line = %s]\n", *line);
		free(tmp);
	}
	if (remain != NULL && ft_strchr(remain, '\n') != 0)
	{
		while (remain[i] != '\n')
		{
			line[0][i] = remain[i];
			i++;
		}
		line[0][i] = '\0';
		size = -1;
	}
	return (size);
}

t_gnl	treat(t_gnl gnl, char *remain, int fd)//
{
	char *tmp;

	if ((remain != NULL && ft_strchr(remain, '\n') == 0) || remain == NULL)
		while ((gnl.rd = read(fd, gnl.buf, BUFF_SIZE)) > 0)
		{
			gnl.i = 0;
			gnl.buf[gnl.rd] = '\0';
			while (gnl.i < gnl.rd && gnl.buf[gnl.i - 1] != '\n')
				gnl.i++;
			gnl.size += gnl.i;
			tmp = malloc(sizeof(char *) * (gnl.size + 1));
			gnl.tmpline = ft_strdup(concatenate(gnl.tmpline, gnl.buf, gnl.size, tmp));//
			free(tmp);
			if (ft_strchr(gnl.buf, '\n') != 0 || gnl.rd < BUFF_SIZE)
				break ;
		//	ft_strdel(&gnl.tmpline);//
		}
	return (gnl);
}

int		get_next_line(const int fd, char **line)
{
	static	t_gnl	gnl;

//	gnl.rd = 0;
	if (gnl.remain == NULL)
		gnl.remain = ft_strnew(BUFF_SIZE);
	ft_memset(gnl.buf, '\0', BUFF_SIZE);
	if (BUFF_SIZE < 1 || fd < 0 || line == NULL)
		return (-1);
	gnl.size = use_remain(line, gnl.remain);
	gnl = treat(gnl, gnl.remain, fd); //*line
	if (gnl.tmpline != NULL)//
	{
		*line = ft_strdup(gnl.tmpline);
		ft_strdel(&gnl.tmpline);
	}//
	if (gnl.rd < 0)
		return (-1);
	if ((ft_strcmp(gnl.remain, "") == 0 && gnl.rd == 0))
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
	printf("[remain = %s]\n", gnl.remain);
	return (1);
}

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
		printf("%d[final line = %s]\n",ret, line);
		if (ret == 0)
			break;
	}
	while (fd != 0)
		ret++;
	return (0);
}
