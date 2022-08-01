/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_threads.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 14:06:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/01 11:29:28 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*checker_thread(void *arg)
{	
	uint16_t	i;
	t_sim		*data;

	data = arg;
	i = 0;
	pthread_mutex_lock(&data->mutex[UTIL_THREAD_START]);
	pthread_mutex_unlock(&data->mutex[UTIL_THREAD_START]);
	while (data->is_running)
	{
		pthread_mutex_lock(&data->philo[i].self);
		if (time_delta_msec(data->philo[i].last_ate, get_time())
			> (uint32_t) data->attr[T_DIE])
		{
			log_status(&data->philo[i], DIED, get_time());
			pthread_mutex_lock(&data->mutex[SIM_RUN]);
			data->is_running = false;
			pthread_mutex_unlock(&data->mutex[SIM_RUN]);
			return (NULL);
		}
		pthread_mutex_unlock(&data->philo[i].self);
		i = (i + 1) % data->attr[N_PHILO];
		usleep(500);
	}
	return (NULL);
}

void	*printer_thread(void *arg)
{
	uint16_t	i;
	t_sim		*data;

	data = arg;
	i = 0;
	while (true)
	{
		pthread_mutex_lock(&data->mutex[QUEUE_RW]);
		if (data->queue[i].status != UNDEFINED)
		{
			print_status(data->queue[i]);
			if (data->queue[i].status == DIED)
			{
				unlock_all(data);
				return (NULL);
			}
			data->queue[i].status = UNDEFINED;
			i = (i + 1) % QUEUE_SIZE;
		}
		pthread_mutex_unlock(&data->mutex[QUEUE_RW]);
		usleep(500);
	}
	return (NULL);
}
