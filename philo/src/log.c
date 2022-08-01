/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 20:36:23 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/01 11:24:30 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_status(t_log log)
{
	const char			*msg[5] = {"is thinking", "is eating", "is sleeping", \
									"has taken a fork", "died"};

	printf(LOG_FMT, log.timestamp, log.philo_id, msg[log.status]);
}

void	log_status(t_philo *data, uint16_t status, t_time time)
{
	static u_int16_t	i;
	t_log				log;

	pthread_mutex_lock(&data->sim_data->mutex[LOG_RW]);
	log.timestamp = time_delta_msec(data->sim_data->start_time, time);
	log.status = status;
	log.philo_id = data->id;
	pthread_mutex_lock(&data->sim_data->mutex[QUEUE_RW]);
	data->sim_data->queue[i] = log;
	i = (i + 1) % QUEUE_SIZE;
	pthread_mutex_unlock(&data->sim_data->mutex[QUEUE_RW]);
	pthread_mutex_unlock(&data->sim_data->mutex[LOG_RW]);
}
