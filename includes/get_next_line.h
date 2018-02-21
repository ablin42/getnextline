#ifndef __GET_NEXT_LINE_H
# define __GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include "../Libft/libft.h"

# define BUFF_SIZE 22

typedef	struct	s_gnl
{
	char	*remain;
	char	buf[BUFF_SIZE + 1];
	int		rd;
	int		size;
	int		i;

}				t_gnl;

int		get_next_line(const int fd, char **line);
#endif
