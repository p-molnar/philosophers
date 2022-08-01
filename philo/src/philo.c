/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 21:20:35 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/01 19:16:31 by pmolnar       ########   odam.nl         */
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

void	philo_eat(t_philo *data)
{
	t_time		time;

	grab_fork(data, data->fork[LEFT]);
	grab_fork(data, data->fork[RGHT]);
	time = get_time();
	data->last_ate = time;
	log_status(data, EATING, time);
	precise_sleep(data->sim_data->attr[T_EAT]);
	pthread_mutex_lock(&data->self);
	data->eat_count++;
	pthread_mutex_unlock(&data->self);
	pthread_mutex_unlock(data->fork[LEFT]);
	pthread_mutex_unlock(data->fork[RGHT]);
}

void	philo_sleep(t_philo *data)
{
	log_status(data, SLEEPING, get_time());
	precise_sleep(data->sim_data->attr[T_SLEEP]);
}

void	run_philo_routine(t_philo *philo, uint16_t status)
{
	bool		sim_running;

	sim_running = philo->sim_data->is_running;
	while (sim_running)
	{
		if (status == THINKING)
			philo_think(philo);
		else if (status == EATING)
			philo_eat(philo);
		else if (status == SLEEPING)
			philo_sleep(philo);
		status = (status + 1) % N_MAIN_STATUS;
		pthread_mutex_lock(&philo->sim_data->mutex[SIM_RUN]);
		sim_running = philo->sim_data->is_running;
		pthread_mutex_unlock(&philo->sim_data->mutex[SIM_RUN]);
	}
}

void	*philo_thread(void *arg)
{
	t_philo		*philo;
	bool		sim_running;
	uint16_t	status;

	philo = arg;
	pthread_mutex_lock(&philo->sim_data->mutex[SIM_INIT]);
	pthread_mutex_unlock(&philo->sim_data->mutex[SIM_INIT]);
	if (philo->id == philo->sim_data->attr[N_PHILO])
		pthread_mutex_unlock(&philo->sim_data->mutex[UTIL_THREAD_START]);
	sim_running = philo->sim_data->is_running;
	philo->last_ate = philo->sim_data->start_time;
	philo_think(philo);
	if (philo->id % 2)
		precise_sleep(1);
	status = EATING;
	run_philo_routine(philo, status);
	return (EXIT_SUCCESS);
}
