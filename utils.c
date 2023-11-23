#include "philo2.h"

int	ft_atoi(const char *nptr)
{
	int				i;
	unsigned int	num;

	i = 0;
	num = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)(num));
}

int	checkforint(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

int	checkargs(char **argv, int argc)
{
	int	i;

	i = 0;
	if (argc < 4 || argc > 6)
	{
		write(1, "you need 3 or 4 arguments!", 26);
		return (0);
	}
	while (argv[++i])
	{
		if (!checkforint(argv[i]))
			return (0);
	}
	return (1);
}
