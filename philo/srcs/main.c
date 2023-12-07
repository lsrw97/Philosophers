/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:46:30 by eelisaro          #+#    #+#             */
/*   Updated: 2023/12/07 16:17:21 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	allfull(t_philo *table)
{
	t_philo	*tmp;

	tmp = table;
	if (getmeals(tmp) != tmp->status->meals)
		return (0);
	tmp = tmp->next;
	while (tmp != table)
	{
		if (getstatusdead(table->status))
			return (0);
		if (getmeals(tmp) != tmp->status->meals)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	takeforks(t_philo *philo)
{
	while (1)
	{
		if (getstatusdead(philo->status))
			return ;
		if (getforks(philo))
		{
			if (getstatusdead(philo->status))
				return ;
			print_msg(philo, philo->index, "has taken a fork\n");
			print_msg(philo, philo->index, "has taken a fork\n");
			break ;
		}
		if (philo->mode != THINKING)
		{
			philo->mode = THINKING;
			print_msg(philo, philo->index, "is thinking\n");
		}
	}
}

void	setjoined(t_philo *philo)
{
	pthread_mutex_lock(&philo->status->mutex_joined);
	philo->status->joined++;
	pthread_mutex_unlock(&philo->status->mutex_joined);
}

void	freetable(t_philo *stack)
{
	t_philo	*node;
	t_philo	*tmp;

	node = stack;
	tmp = stack->prev;
	while (stack->index != tmp->index)
	{
		stack = stack->next;
		free(node);
		node = stack;
	}
	free(node);
}

int	main(int argc, char **argv)
{
	pthread_t	*philos;
	pthread_t	check;
	t_status	*status;
	t_philo		*table;

	if (!checkargs(argv, argc))
		return (0);
	philos = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	if (!philos)
		return (0);
	status = malloc(sizeof(t_status));
	table = createtable(ft_atoi(argv[1]), status);
	status = instatus(argv, status, table, argc);
	pthread_create(&check, NULL, &checker, table);
	createthreads(table, philos);
	if (jointhreads(philos, ft_atoi(argv[1]), table))
	{
		pthread_join(check, NULL);
		freetable(table);
		free(status);
		free(philos);
	}
	return (0);
}
