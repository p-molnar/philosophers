/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 21:20:35 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/05 13:45:10 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	run_philo_routine(t_philo *philo, uint16_t status)
{
	bool		sim_running;

	pthread_mutex_lock(&philo->sim_data->mutex[SIM_RUN]);
	sim_running = philo->sim_data->is_running;
	pthread_mutex_unlock(&philo->sim_data->mutex[SIM_RUN]);
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
