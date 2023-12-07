/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:11:48 by eelisaro          #+#    #+#             */
/*   Updated: 2023/11/27 12:23:06 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	getstatusdead(t_status *status)
{
	int	dead;

	pthread_mutex_lock(&status->deathmutex);
	dead = status->dead;
	pthread_mutex_unlock(&status->deathmutex);
	return (dead);
}

unsigned long long	getstatustime(t_status *status)
{
	unsigned long long	time;

	pthread_mutex_lock(&status->mutex_time);
	time = status->time;
	pthread_mutex_unlock(&status->mutex_time);
	return (time);
}
