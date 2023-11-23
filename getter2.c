#include "philo2.h"

int	getmeals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->mutex_meals);
	meals = philo->meals;
	pthread_mutex_unlock(&philo->mutex_meals);
	return (meals);
}

int	getlastmeal(t_philo *philo)
{
	int	lastmeal;

	pthread_mutex_lock(&philo->mutex_lastmeal);
	lastmeal = philo->lastmeal;
	pthread_mutex_unlock(&philo->mutex_lastmeal);
	return (lastmeal);
}

int	getfork(t_philo *philo, int i)
{
	int fork;
	if (philo->index + i - 1 == philo->status->pcount)
		fork = philo->status->forks[0];
	else
		fork = philo->status->forks[philo->index + i - 1];
	return (fork);
}

int	getforks(t_philo *philo)
{
	pthread_mutex_lock(&philo->status->mutex_fork);
	if (getfork(philo, 0) && getfork(philo, 1))
	{
		togglefork(philo, 0);
		togglefork(philo, 1);
	}
	else
	{
		pthread_mutex_unlock(&philo->status->mutex_fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->status->mutex_fork);
	return (1);
}
