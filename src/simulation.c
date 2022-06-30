/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 14:40:24 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/30 14:54:02 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void static	run_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim_attr->start_lock);
	pthread_mutex_unlock(&philo->sim_attr->start_lock);
	philo->last_time_eaten = philo->sim_attr->start_time;
	while (philo->sim_attr->all_philo_alive == true)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
}

static int	join_threads(t_philo *philo_arr, t_sim_data *attr)
{
	size_t	i;

	if (pthread_join(attr->printer, NULL))
		return (error_handler(THREAD_ERROR, "launch_simulation, j_thread"));
	if (pthread_join(attr->checker, NULL))
		return (error_handler(THREAD_ERROR, "launch_simulation, j_thread"));
	i = 0;
	while (i < (size_t)attr->n_philo)
	{
		if (pthread_join(philo_arr[i].thread, NULL))
			return (error_handler(THREAD_ERROR, "join_threads, j_thread"));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_threads(t_philo *philo_arr, t_sim_data *attr)
{
	size_t	i;

	if (pthread_create(&attr->printer, NULL,
			(void *) &print_queue, (void *)attr))
	{
		return (error_handler(THREAD_ERROR, "init_threads, c_thread"));
	}
	if (pthread_create(&attr->checker, NULL,
			(void *) &check_status, (void *)philo_arr))
	{
		return (error_handler(THREAD_ERROR, "init_threads, c_thread"));
	}
	i = 0;
	while (i < (size_t)attr->n_philo)
	{
		if (pthread_create(&philo_arr[i].thread, NULL, \
		(void *) &run_philo_routine, (void *) &philo_arr[i]))
		{
			return (error_handler(THREAD_ERROR, "init_threads, c_thread"));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	init_mutexes(t_sim_data *attr)
{	
	size_t	i;

	if (pthread_mutex_init(&attr->start_lock, NULL))
		return (error_handler(MUTEX_ERROR, "init_mutexes, m_init"));
	if (pthread_mutex_init(&attr->monitoring_lock, NULL))
		return (error_handler(MUTEX_ERROR, "init_mutexes, m_init"));
	if (pthread_mutex_init(&attr->queue_lock, NULL))
		return (error_handler(MUTEX_ERROR, "init_mutexes, m_init"));
	i = 0;
	while (i < (size_t)attr->n_philo)
	{
		if (pthread_mutex_init(attr->forks[i], NULL))
			return (error_handler(MUTEX_ERROR, "init_mutexes, m_init"));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	launch_simulation(t_philo *philo_arr, t_sim_data *attr)
{
	init_mutexes(attr);
	pthread_mutex_lock(&attr->start_lock);
	init_threads(philo_arr, attr);
	attr->start_time = get_time();
	pthread_mutex_unlock(&attr->start_lock);
	join_threads(philo_arr, attr);
	// destroy_mutexes(attr);
	return (EXIT_SUCCESS);
}
