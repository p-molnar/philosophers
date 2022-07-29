/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_threads.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 14:06:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/29 14:18:19 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	checker(t_sim *data)
{	
	uint16_t	i;
	t_time		curr_time;

	i = 0;
	pthread_mutex_lock(&data->mutex[UTIL_START]);
	pthread_mutex_unlock(&data->mutex[UTIL_START]);
	while (data->is_running)
	{
		curr_time = get_time();
		pthread_mutex_lock(&data->philo[i].self);
		if (time_delta_msec(data->philo[i].last_ate, curr_time) > (uint32_t) data->attr[T_DIE])
		{
			printf("diff: %d\n", time_delta_msec(data->philo[i].last_ate, curr_time));
			log_status(&data->philo[i], DIED, curr_time);
			data->is_running = false;
			return ;
		}
		pthread_mutex_unlock(&data->philo[i].self);
		if (++i == data->attr[N_PHILO])
			i = 0;
		usleep(500);
	}
}

void	printer(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (true)
	{
		pthread_mutex_lock(&data->mutex[QUEUE]);
		if (data->queue[i].status != UNDEFINED)
		{
			print_status(data->queue[i]);
			if (data->queue[i].status == DIED)
			{
				unlock_all(data);
				return ;
			}
			data->queue[i].status = UNDEFINED;
			if (++i == QUEUE_SIZE)
				i = 0;
		}
		pthread_mutex_unlock(&data->mutex[QUEUE]);
		usleep(500);
	}
}
