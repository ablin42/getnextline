#include "get_next_line.h"
#include <stdio.h>

t_lst	*add_list(t_lst *lst, int fd)
{
	t_lst	*element;
	t_lst	*tmp;

	if ((element = malloc(sizeof(t_lst))) == NULL)
		return (NULL);
	tmp = lst;
	element->str = ft_strnew(1);//moche
	element->fd = fd;
	if (lst == NULL)
		return (element);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = element;
	return (lst);
}

t_lst		*fetch_fd(t_lst **lst, int fd)
{
	t_lst		*tmp;
	
	tmp = *lst;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = add_list(tmp, fd);
	return (tmp);
}

char		*save_remain(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = ft_strdup(str);
	i = 0;
	j = 0;
	ft_strclr(str);
	while (tmp[i] != '\0' && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
		i++;
	ft_strcpy(str, &tmp[i]);
	free(tmp);
	return (str);
}

char	*ft_strjoinfree(char const *s1, char const *s2)
{
	char	*tmp;

	if (!s1 || !s2 || (tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2))) == NULL)
		return (NULL);
	tmp = ft_strcpy(tmp, s1);
	tmp = ft_strcat(tmp, s2);
	ft_strdel((char **)&s1);
	return (tmp);
}

int			get_next_line(const int fd, char **line)
{
	t_gnl				gnl;
	static	t_lst		*lst;
//	char				*tmp;

	if (BUFF_SIZE < 1 || fd < 0 || line == NULL || read(fd, gnl.buf, 0) < 0)
		return (-1);
	if ((lst = fetch_fd(&lst, fd)) == NULL)
		return (-1);
	//ft_strclr(*line);
	*line = ft_strnew(1);
	while ((gnl.rd = read(fd, gnl.buf, BUFF_SIZE)) >= 0)
	{
		gnl.buf[gnl.rd] = '\0';
	//	tmp = ft_strdup(lst->str);
	//	free(lst->str);
		if ((lst->str = ft_strjoin(lst->str, gnl.buf)) == NULL)
			return (-1);
	//	free(tmp);
		if (ft_strchr(gnl.buf, '\n') != 0 || gnl.rd < BUFF_SIZE)
			break;
	}
	//if (gnl.rd < 0)
	//	return (-1);
	if (gnl.rd == 0 && ft_strcmp(lst->str, "") == 0)
		return (0);
	gnl.size = 0;
	while (lst->str[gnl.size] != '\0' && lst->str[gnl.size] != '\n')
		gnl.size++;
	*line = ft_strndup(lst->str, gnl.size);///////
	lst->str = save_remain(lst->str);
	return (1);
}
/*
int	main()
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcd\n", 5);
	write(fd, "efgh\n", 5);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	printf("%d\n", ft_strcmp(line, "abcd"));
	get_next_line(p[0], &line);
	printf("%d\n", ft_strcmp(line, "efgh"));
	ret = get_next_line(p[0], &line);
	printf("%d\n", ret);
	return (0);
}*/

/*/
int		main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	*line;
	int		i;

	i = 0;
	(void)argc;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		printf("%d[%s]%d\n", ret, line, i);
		i++;
		if (ret == 0)
			break;
	}
	return (0);
}//*/
