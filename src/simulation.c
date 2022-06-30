/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 14:40:24 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/29 15:23:20 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void static	run_philo_life_cycle(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim_attr->start_lock);
	pthread_mutex_unlock(&philo->sim_attr->start_lock);
	philo->last_time_eaten = philo->sim_attr->start_time;

	while (philo->sim_attr->all_philo_alive == true)
	{
		if (philo_think(philo))
			break ;
		if (philo_eat(philo))
			break ;
		if (philo_sleep(philo))
			break ;
	}
	return ;
}

static int	create_thread(t_philo *philo)
{
	if (pthread_create(&philo->philo_thread, NULL, \
		(void *) &run_philo_life_cycle, (void *) philo))
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	join_thread(t_philo *philo)
{
	if (pthread_join(philo->philo_thread, NULL))
		return (error_handler(THREAD_ERROR, "join_threads, j_thread"));
	return (EXIT_SUCCESS);
}

int	launch_simulation(t_philo *philo_arr, t_attr *attr)
{
	size_t		i;

	i = 0;
	if (pthread_mutex_init(&attr->queue_lock, NULL))
		return (error_handler(MUTEX_ERROR, "launch_simulation, m_init"));
	if (pthread_mutex_init(&attr->start_lock, NULL))
		return (error_handler(MUTEX_ERROR, "launch_simulation, m_init"));
	gettimeofday(&attr->start_time, NULL);
	while (i < (size_t)attr->n_philo)
	{
		pthread_mutex_lock(&attr->queue_lock);
		if (pthread_mutex_init(attr->forks[i], NULL))
			return (error_handler(MUTEX_ERROR, "launch_simulation, m_init"));
		if (create_thread(&philo_arr[i]))
			return (error_handler(THREAD_ERROR, "launch_simulation, c_thread"));
		i++;
		usleep(1);
		pthread_mutex_unlock(&attr->queue_lock);
	}
	if (pthread_create(&attr->printer_thread, NULL, (void *) &print_queue, (void *)attr))
		return (error_handler(THREAD_ERROR, "launch_simulation, c_thread"));	
	if (pthread_create(&attr->monitoring_thread, NULL, (void *) &status_monitoring, (void *)philo_arr))
		return (error_handler(THREAD_ERROR, "launch_simulation, c_thread"));
	if (pthread_join(attr->printer_thread, NULL))
		return (error_handler(THREAD_ERROR, "launch_simulation, j_thread"));
	if (pthread_join(attr->monitoring_thread, NULL))
		return (error_handler(THREAD_ERROR, "launch_simulation, j_thread"));
	i = 0;
	while (i < (size_t)attr->n_philo)
	{
		if (join_thread(&philo_arr[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
