/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:15:48 by eelisaro          #+#    #+#             */
/*   Updated: 2023/12/07 16:17:50 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*checker(void *arg)
{
	t_philo	*table;

	table = (t_philo *)arg;
	while (get_time() - table->status->time - getlm(table) 
		< (long long unsigned int)table->status->lt)
	{
		if (allfull(table))
			return (NULL);
		table = table->next;
	}
	print_msg(table, table->index, "died\n");
	setstatusdead(table->status);
	while (!getjoined(table))
		usleep(25);
	return (NULL);
}

int	jointhreads(pthread_t *threads, int size, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < size)
		pthread_join(threads[i], NULL);
	setjoined(philo);
	return (1);
}

void	subroutine(t_philo *philo)
{
	print_msg(philo, philo->index, "is eating\n");
	ft_sleep(philo->status->eattime, get_time());
	setlastmeal(philo);
	incrementmeals(philo);
	togglephilofork(philo);
	togglephilofork(philo->next);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (getstatusdead(philo->status))
			return (NULL);
		if (philo->mode != THINK && philo->meals != philo->status->meals)
		{
			takeforks(philo);
			if (getstatusdead(philo->status))
				return (NULL);
			subroutine(philo);
		}
		if (allfull(philo))
			return (NULL);
		if (getstatusdead(philo->status))
			return (NULL);
		philo->mode = SLEEP;
		print_msg(philo, philo->index, "is sleeping\n");
		ft_sleep(philo->status->sleeptime, get_time());
		usleep(3);
	}
}

int	createthreads(t_philo *table, pthread_t *philos)
{
	t_philo	*tmp;
	int		i;

	i = -1;
	tmp = table;
	while (tmp->next->index != table->index)
	{
		pthread_create(&philos[++i], NULL, &routine, tmp);
		tmp = tmp->next;
	}
	pthread_create(&philos[++i], NULL, &routine, tmp);
	return (1);
}
