/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_actions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/05 13:45:47 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/05 13:48:50 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_think(t_philo *data)
{
	log_status(data, THINKING, get_time());
}

void	grab_fork(t_philo *data, t_mutex *mutex)
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
	log_status(data, EATING, time);
	pthread_mutex_lock(&data->self);
	data->last_ate = time;
	data->eat_count++;
	pthread_mutex_unlock(&data->self);
	precise_sleep(data->sim_data->attr[T_EAT]);
	pthread_mutex_unlock(data->fork[LEFT]);
	pthread_mutex_unlock(data->fork[RGHT]);
}

void	philo_sleep(t_philo *data)
{
	log_status(data, SLEEPING, get_time());
	precise_sleep(data->sim_data->attr[T_SLEEP]);
}
