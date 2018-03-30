#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

//*/
int		main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	*line;
//	int		i;

//	system("openssl rand -base64 $((250000))  > sandbox/one_big_fat_line.txt");
//	i = 0;
	(void)argc;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		printf("%d[%s]\n", ret, line);
//		i++;
		if (ret == 0)
			break;
	}
	return (0);
}//*/
