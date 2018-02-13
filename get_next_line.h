#ifndef __GET_NEXT_LINE_H
# define __GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include "Libft/libft.h"

# define BUFF_SIZE 35

int		get_next_line(const int fd, char **line);
#endif
