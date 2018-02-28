#include "Libft/ft_putstr.c"
#include "leaks.h"

t_leaks		leak(t_leaks lk)
{
	char	letter;
	int		i;

	letter = 'a';
	i = 0;
	lk.str = malloc(sizeof(char *) * (10 + 1));
	while (i < 10)
	{
		lk.str[i] = letter;
		letter++;
		i++;
	}
	return (lk);
}

int		xd(t_leaks lk)
{

	t_leaks lk;
}

int		main()
{
	int i;
	i = 0;
	lk = leak(lk);
	ft_putstr(lk.str);
	while (i != -1)
	{
		i++;
		i--;
	}
	return (0);
}
