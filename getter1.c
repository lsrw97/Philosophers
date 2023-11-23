#include "philo2.h"

int	getstatusdead(t_status *status)
{
	int	dead;
	pthread_mutex_lock(&status->deathmutex);
	dead = status->dead;
	pthread_mutex_unlock(&status->deathmutex);
	return (dead);
}

unsigned long long getstatustime(t_status *status)
{
	unsigned long long	time;
	pthread_mutex_lock(&status->mutex_time);
	time = status->time;
	pthread_mutex_unlock(&status->mutex_time);
	return (time);
}

unsigned long long	getstatuscurrenttime(t_status *status)
{
	unsigned long long	currenttime;
	pthread_mutex_lock(&status->mutex_currenttime);
	currenttime = status->currenttime;
	pthread_mutex_unlock(&status->mutex_currenttime);
	return (currenttime);
}

t_philo	*getphilo(t_philo *philo)
{
	t_philo *philosopher;
	pthread_mutex_lock(&philo->mutex_philo);
	philosopher = philo;
	pthread_mutex_unlock(&philo->mutex_philo);
	return (philosopher);
}

int	getindex(t_philo *philo)
{
	int	index;
	pthread_mutex_lock(&philo->mutex_index);
	index = philo->index;
	pthread_mutex_unlock(&philo->mutex_index);
	return (index);
}
