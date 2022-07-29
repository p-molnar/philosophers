/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 21:20:35 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/29 14:23:14 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	philo_think(t_philo *data)
{
	log_status(data, THINKING, get_time());
}

static void	grab_fork(t_philo *data, t_mutex *mutex)
{
	pthread_mutex_lock(mutex);
	log_status(data, TAKING_FORK, get_time());
}

static void	put_fork(t_mutex *mutex)
{
	pthread_mutex_unlock(mutex);
}
static void	grab_forks(t_philo *data)
{
	uint16_t	n_philo;

	n_philo = data->sim_data->attr[N_PHILO];
	if (n_philo % 2)
	{
		if (data->id % 2 || data->id == n_philo)
		{
			usleep(10);
			grab_fork(data, data->fork[LEFT]);
			grab_fork(data, data->fork[RGHT]);
		}
		else
		{
			grab_fork(data, data->fork[RGHT]);
			grab_fork(data, data->fork[LEFT]);
		}
	}
	else
	{
		if (data->id % 2)
		{
			grab_fork(data, data->fork[LEFT]);
			grab_fork(data, data->fork[RGHT]);
		}
		else
		{
			grab_fork(data, data->fork[RGHT]);
			grab_fork(data, data->fork[LEFT]);
		}
	}
}

void	philo_eat(t_philo *data)
{
	t_time		time;
	uint16_t	n_philo;

	n_philo = data->sim_data->attr[N_PHILO];
	grab_forks(data);
	time = get_time();
	precise_sleep(data->sim_data->attr[T_EAT]);
	log_status(data, EATING, time);
	data->last_ate = time;
	if (data->id % 2)
	{
		put_fork(data->fork[RGHT]);
		put_fork(data->fork[LEFT]);
	}
	else
	{
		put_fork(data->fork[RGHT]);
		put_fork(data->fork[LEFT]);
	}
}

void	philo_sleep(t_philo *data)
{
	log_status(data, SLEEPING, get_time());
	precise_sleep(data->sim_data->attr[T_SLEEP]);
}

void	*simulation(void *arg)
{
	t_philo	*philo;
	bool	sim_running;

	philo = arg;
	pthread_mutex_lock(&philo->sim_data->mutex[INIT]);
	pthread_mutex_unlock(&philo->sim_data->mutex[INIT]);
	philo->last_ate = philo->sim_data->start_time;
	sim_running = philo->sim_data->is_running;
	if (philo->id == philo->sim_data->attr[N_PHILO])
		pthread_mutex_unlock(&philo->sim_data->mutex[UTIL_START]);
	while (sim_running)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
		sim_running = philo->sim_data->is_running;
	}
	return (EXIT_SUCCESS);
}
