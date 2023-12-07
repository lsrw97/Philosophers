/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:12:15 by eelisaro          #+#    #+#             */
/*   Updated: 2023/12/07 16:50:05 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned int	ft_atoi(const char *nptr)
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
	return ((num));
}

int	checkforint(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	if (ft_strlen(str) > 10)
		return (0);
	if (ft_atoi(str) > 2147483647 || ft_atoi(str) == 0)
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
	if (argc < 5 || argc > 6)
	{
		write(1, "You need 4 or 5 arguments!", 26);
		return (0);
	}
	if (ft_atoi(argv[1]) == 0)
	{
		printf("Number of philos can't be zero!! Nice try asshole\n");
		return (0);
	}
	while (argv[++i])
	{
		if (!checkforint(argv[i]))
		{
			printf("Argument is not positive number or too large!\n");
			return (0);
		}
	}
	return (1);
}

void	print_msg(t_philo *philo, int index, char *msg)
{
	unsigned long long	time;

	time = get_time() - philo->status->time;
	pthread_mutex_lock(&philo->status->mutex_msg);
	if (getstatusdead(philo->status))
	{
		pthread_mutex_unlock(&philo->status->mutex_msg);
		return ;
	}
	printf("%llu %d %s", time, index, msg);
	pthread_mutex_unlock(&philo->status->mutex_msg);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}