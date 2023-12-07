/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:12:38 by eelisaro          #+#    #+#             */
/*   Updated: 2023/11/27 15:09:34 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	getmeals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->status->mutex_meals);
	meals = philo->meals;
	pthread_mutex_unlock(&philo->status->mutex_meals);
	return (meals);
}

int	getlm(t_philo *philo)
{
	int	lastmeal;

	pthread_mutex_lock(&philo->mutex_lastmeal);
	lastmeal = philo->lastmeal;
	pthread_mutex_unlock(&philo->mutex_lastmeal);
	return (lastmeal);
}

int	getforks(t_philo *philo)
{
	if (getstatusdead(philo->status))
		return (0);
	if (getphilofork(philo) && getphilofork(philo->next) 
		&& philo->index != philo->next->index)
	{
		togglephilofork(philo);
		togglephilofork(philo->next);
	}
	else
		return (0);
	return (1);
}
