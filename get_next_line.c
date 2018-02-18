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

unsigned long	use_remain(char **line, char *remain)
{
	int		i;
	int		size;
	char	*tmp;

	i = 0;
	size = 0;
	if (remain != NULL)
	{
		size = ft_strlen(remain);
		tmp = malloc(sizeof(char *) * size);
		*line = concatenate(remain, NULL, ft_strlen(remain), tmp);
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

t_gnl	treat(t_gnl gnl, char **line, char *remain, int fd)
{
	char *tmp;

	if ((remain != NULL && ft_strchr(remain, '\n') == 0) || remain == NULL)
	while ((gnl.rd = read(fd, gnl.buf, BUFF_SIZE)) > 0)
	{
		gnl.i = 0;
		gnl.buf[gnl.rd] = '\0';
		while (gnl.i < gnl.rd && gnl.buf[gnl.i - 1] != '\n') // segfault
			gnl.i++;
		gnl.size += gnl.i;
		tmp = malloc(sizeof(char *) * gnl.size);
		*line = concatenate(*line, gnl.buf, gnl.size, tmp);
		free(tmp);
		if (ft_strchr(gnl.buf, '\n') != 0 || gnl.rd < BUFF_SIZE)
			break;
	}
	return (gnl);
}

// line is the string we read, minus the terminating \n
int		get_next_line(const int fd, char **line)
{
	static	char	*remain;
	t_gnl			gnl;

	ft_strclr(gnl.buf);
	if (BUFF_SIZE < 1 || fd < 0)//line == null
		return (-1);
	gnl.size = use_remain(line, remain);
	gnl = treat(gnl, line, remain, fd);
	if (gnl.rd < 0)
		return (-1);
	if (ft_strcmp(*line, "") == 0 || (remain == NULL && gnl.rd == 0))//gnl.rd == 0
		return (0);
	if (gnl.size != -1)
		remain = ft_strdup(gnl.buf);
	if (ft_strchr(remain, '\n') != 0)
	{
		remain = ft_strchr(remain, '\n');//probablement need \0
		remain++;
	}
	else
		remain = NULL;
	return (1);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	int		ret;
	char	**line;

	(void)argc;
	line = malloc(sizeof(char **) * 8);
	*line = NULL;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	if ((fd2 = open(argv[2], O_RDONLY)) == -1)
		return (0);
	ret = get_next_line(fd, line);
	printf("%d[1final line = %s]\n",ret, *line);
	ret = get_next_line(fd2, line);
	printf("%d[2final line = %s]\n",ret, *line);
	ret = get_next_line(fd, line);
	printf("%d[1final line = %s]\n",ret, *line);
	ret = get_next_line(fd2, line);
	printf("%d[2final line = %s]\n",ret, *line);
	ret = get_next_line(fd, line);
	printf("%d[1final line = %s]\n",ret, *line);
	ret = get_next_line(fd2, line);
	printf("%d[2final line = %s]\n",ret, *line);
	
/*	while ((ret = get_next_line(fd, line)) > 0)
	{
		printf("%d[final line = %s]\n",ret, *line);
		if (ret == 0)
			break;
	}*/
	return (0);
}
