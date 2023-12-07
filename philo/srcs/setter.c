/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:12:27 by eelisaro          #+#    #+#             */
/*   Updated: 2023/12/07 16:17:41 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	setstatusdead(t_status *status)
{
	pthread_mutex_lock(&status->deathmutex);
	status->dead++;
	pthread_mutex_unlock(&status->deathmutex);
}

void	togglephilofork(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	if (philo->fork)
		philo->fork = 0;
	else
		philo->fork = 1;
	pthread_mutex_unlock(&philo->mutex_fork);
}

void	setlastmeal(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_lastmeal);
	philo->lastmeal = get_time() - philo->status->time;
	pthread_mutex_unlock(&philo->mutex_lastmeal);
}

void	incrementmeals(t_philo *philo)
{
	pthread_mutex_lock(&philo->status->mutex_meals);
	philo->meals++;
	pthread_mutex_unlock(&philo->status->mutex_meals);
}

int	getphilofork(t_philo *philo)
{
	int	fork;

	pthread_mutex_lock(&philo->mutex_fork);
	fork = philo->fork;
	pthread_mutex_unlock(&philo->mutex_fork);
	return (fork);
}
