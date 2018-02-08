#include "get_next_line.h"

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
	while (i < size)
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
	char	*str;
	int		rd;
	unsigned long		size;
	int		i;

	if (BUFF_SIZE < 1)
		return (-1);
	(void)line;
	str = NULL;
	size = 0;
	while ((rd = read(fd, buf, BUFF_SIZE)) != 0)
	{
		i = 0;
		while (i < BUFF_SIZE && buf[i - 1] != '\n') //care segfault
			i++;
		size += i;
		//if ((str = (char*)malloc(sizeof(char *) * (size + 1))) == NULL)
		//	return (0);
		str = concatenate(str, buf, size);
		if (buf[i - 1] == '\n')
			break;
	}
	ft_putstr(*line);
	*line = str;
	ft_putstr(*line);
	if (strcmp(*line,"lorem ipsum dolor\n") == 0)
		get_next_line(fd, line);
	return (1);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	**line;

	(void)argc;
	line = malloc(sizeof(char **) * 8);
	*line = "hello!\n";
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	get_next_line(fd, line);
	return (0);
}
