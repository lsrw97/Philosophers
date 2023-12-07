/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:03:31 by eelisaro          #+#    #+#             */
/*   Updated: 2023/12/07 16:48:12 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_status	*instatus(char **av, t_status *status, t_philo *ph, int i)
{
	status->joined = 0;
	status->pcount = ft_atoi(av[1]);
	status->lt = ft_atoi(av[2]);
	status->eattime = ft_atoi(av[3]);
	status->sleeptime = ft_atoi(av[4]);
	if (i == 6)
		status->meals = ft_atoi(av[5]);
	else
		status->meals = INT_MAX;
	status->time = get_time();
	status->table = ph;
	status->dead = 0;
	pthread_mutex_init(&status->deathmutex, NULL);
	pthread_mutex_init(&status->mutex_joined, NULL);
	pthread_mutex_init(&status->mutex_msg, NULL);
	pthread_mutex_init(&status->mutex_meals, NULL);
	return (status);
}

t_philo	*newnode(t_philo *prev, int i, t_status *status)
{
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->status = status;
	if (!(i % 2))
		philo->mode = EAT;
	else
		philo->mode = THINK;
	pthread_mutex_init(&philo->mutex_lastmeal, NULL);
	pthread_mutex_init(&philo->mutex_fork, NULL);
	philo->meals = 0;
	philo->index = i;
	philo->next = NULL;
	philo->prev = prev;
	philo->lastmeal = 0;
	philo->fork = 1;
	return (philo);
}

t_philo	*createtable(int size, t_status *status)
{
	t_philo	*table;
	t_philo	*tmp;
	int		i;

	i = 1;
	table = newnode(NULL, 1, status);
	tmp = table;
	while (++i <= size)
	{
		tmp->next = newnode(tmp, i, status);
		tmp = tmp->next;
	}
	tmp->next = table;
	table->prev = tmp;
	return (table);
}

int	getjoined(t_philo *philo)
{
	int	joined;

	pthread_mutex_lock(&philo->status->mutex_joined);
	joined = philo->status->joined;
	pthread_mutex_unlock(&philo->status->mutex_joined);
	return (joined);
}
