#include "philo2.h"

void	setstatuscurrenttime(t_status *status)
{
	pthread_mutex_lock(&status->mutex_currenttime);
	status->currenttime = get_time() - getstatustime(status);
	pthread_mutex_unlock(&status->mutex_currenttime);
}

void	setstatusdead(t_status *status)
{
	pthread_mutex_lock(&status->deathmutex);
	status->dead++;
	pthread_mutex_unlock(&status->deathmutex);
}

void	togglefork(t_philo *philo, int i)
{
	if (philo->index + i - 1 == philo->status->pcount)
	{
		if (philo->status->forks[0])
			philo->status->forks[0] = 0;
		else
			philo->status->forks[0] = 1;
	}
	else
	{
		if (philo->status->forks[philo->index + i - 1])
			philo->status->forks[philo->index + i - 1] = 0;
		else
			philo->status->forks[philo->index + i - 1] = 1;
	}
}

void	setlastmeal(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_lastmeal);
	philo->lastmeal = get_time() - philo->status->time;
	pthread_mutex_unlock(&philo->mutex_lastmeal);
}

void	incrementmeals(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_meals);
	philo->meals++;
	pthread_mutex_unlock(&philo->mutex_meals);
}
