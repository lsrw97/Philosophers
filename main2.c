#include "philo2.h"

void	print_msg(t_philo *philo, int index, char *msg)
{
	unsigned long long	time;

	time = get_time() - philo->status->time;
	pthread_mutex_lock(&philo->status->mutex_msg);
		// if (!getstatusdead())
			printf("%llu %d %s", time, index, msg);
	pthread_mutex_unlock(&philo->status->mutex_msg);
}



int	allfull(t_philo *table)
{
	t_philo *tmp;
	tmp = table;
	if (getmeals(tmp) != tmp->status->meals)
		return (0);
	tmp = tmp->next;
	while (tmp != table)
	{
		if (getmeals(tmp) != tmp->status->meals)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	takeforks(t_philo *philo)
{
	while (1)
	{
		if (getstatusdead(philo->status))
		{
			philo->mode = DEAD;
			return (0);
		}
		if (getforks(philo))
		{
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

void    *checker(void *arg)
{
	t_philo *table;

	table = (t_philo *)arg;
	while (get_time() - table->status->time - getlastmeal(table) < table->status->lifetime)
	{
		if (allfull(table))
			return (NULL);
		table = table->next;
	}
	print_msg(table, table->index, "died\n");
	pthread_mutex_lock(&table->status->mutex_msg);
	setstatusdead(table->status);
	return (NULL);
}


int	jointhreads(pthread_t   *threads, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		pthread_join(threads[i], NULL);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	while (1)
	{
		if (getstatusdead(philo->status))
		{
			philo->mode = DEAD;
			return (0);
		}
		if (philo->mode != THINK && philo->meals != philo->status->meals)
		{
			takeforks(getphilo(philo));
			if (getstatusdead(philo->status))
			{
				philo->mode = EAT;
				return (0);
			}
				print_msg(philo, philo->index, "is eating\n");
				ft_sleep(philo->status->eattime, get_time());
			setlastmeal(philo);
			incrementmeals(philo);
			pthread_mutex_lock(&philo->status->mutex_fork);
			togglefork(philo, 0);
			togglefork(philo, 1);
			pthread_mutex_unlock(&philo->status->mutex_fork);
		}
		if (allfull(philo))
			return (NULL);
			philo->mode = SLEEP;
		if (getstatusdead(philo->status))
		{
			return (0);
		}
			print_msg(philo, philo->index, "is sleeping\n");
			ft_sleep(philo->status->sleeptime, get_time());
			usleep(1);
	}
	return NULL;
}

int main (int argc, char **argv)
{
	pthread_t   *philos;
	pthread_t	check;
	t_status    *status;
	t_philo     *table;

	if (!checkargs(argv, argc))
		return (0);

	philos = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	if (!philos)
		return (0);
	status = malloc(sizeof(t_status));

	table = createtable(ft_atoi(argv[1]), argv, status);
	status = init_status(argv, status, table, argc);

    // Thread that checks if any philo is DEAD

	pthread_create(&check, NULL, &checker, table);

	createthreads(table, philos);

	// while (1)
	// {
		// if (checkforrunning(table));
		// {
			jointhreads(philos, ft_atoi(argv[1]));
			// break ;
		// }
	// }
	pthread_join(check, NULL);
	free(philos);
	return 0;
}
