/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:02:29 by eelisaro          #+#    #+#             */
/*   Updated: 2023/11/24 19:43:43 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long long	get_time(void)
{
	unsigned long long	time;
	struct timeval		current_time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_usec / 1000 + current_time.tv_sec * 1000;
	return (time);
}

void	ft_sleep(unsigned long long wait, unsigned long long now)
{
	while (1)
	{
		if (get_time() - now >= wait)
			return ;
		usleep(20);
	}
}
