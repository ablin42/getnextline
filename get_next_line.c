#include "get_next_line.h"
#include <stdio.h>


char	*concatenate(char *str, char *buf, unsigned long size)
{
	char	*tmp;
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char *) * size);
	if (str != NULL)
	{
		while (i < ft_strlen(str))
		{
			tmp[i] = str[i];
			i++;
		}
	}
	//printf("[%s]{%s}(%s)\n", tmp, str, buf);
	while (i < size && buf[j] != '\n')
	{
		tmp[i] = buf[j];
		i++;
		j++;
	}
	return (tmp);
}

// line is the string we read, minus the terminating \n
int		get_next_line(const int fd, char **line)
{
	char	buf[BUFF_SIZE];
	static	char	*str;
	int		rd;
	unsigned long		size;
	int		i;

	size = 0;
	i = 0;
	if (BUFF_SIZE < 1)
		return (-1);
	if (str != NULL)
	{
		*line = concatenate(str, NULL, ft_strlen(str));
		size = ft_strlen(str);
	}
	if (str != NULL && ft_strchr(str, '\n') != '\0')//
	{
		while (str[i] != '\n')
		{
			line[0][i] = str[i];
			i++;
		}
		line[0][i] = '\0';
		str = ft_strchr(str, '\n');
		str++;
		printf("[final line = %s]\n", line[0]);
		return (1);
	}
	//str = malloc(sizeof(char *) * (BUFF_SIZE + 1));
	while ((rd = read(fd, buf, BUFF_SIZE)) != 0)
	{
		str = ft_strdup(buf);
		str[BUFF_SIZE] = '\0';
		i = 0;
		while (i < BUFF_SIZE && buf[i - 1] != '\n') //care segfault
			i++;
		size += i;
		*line = concatenate(*line, str, size);
		if (ft_strchr(buf, '\n') != 0)
			break;
	}
	str = ft_strchr(str, '\n');
	str++;
	//printf("[remaining = %s]\n", str);
	printf("[final line = %s]\n", *line);
	return (1);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	**line;

	(void)argc;
	line = malloc(sizeof(char **) * 8);
	*line = NULL;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	get_next_line(fd, line);
	get_next_line(fd, line);
	get_next_line(fd, line);
	get_next_line(fd, line);
	return (0);
}
