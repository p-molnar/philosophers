/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_threads.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 14:06:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/02 00:22:23 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	all_philo_fed(t_sim *data)
{
	uint16_t	i;
	bool		is_philo_fed;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		pthread_mutex_lock(&data->philo[i].self);
		is_philo_fed = data->philo[i].eat_count >= (uint16_t) data->attr[N_EAT];
		pthread_mutex_unlock(&data->philo[i].self);
		if (data->attr[N_EAT] == UNDEFINED || !is_philo_fed)
			return (false);
		i++;
	}
	return (true);
}

static void	print_status(t_log log, t_sim *data)
{
	const char			*msg[6] = {"is thinking", "is eating", "is sleeping", \
									"has taken a fork", "died", "all fed"};
	uint16_t			i;

	if (log.status == ALL_FED)
	{
		printf("\nAll philosophers have eaten\n");
		printf("\n-----   SUMMARY   -----\n");
		i = 0;
		while (i < data->attr[N_PHILO])
		{
			pthread_mutex_lock(&data->philo[i].self);
			printf("philo %d %s: %d time(s)\n", data->philo[i].id, "ate",
				data->philo[i].eat_count);
			pthread_mutex_unlock(&data->philo[i].self);
			i++;
		}
		printf("-----------------------\n");
	}
	else
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
		if (time_delta_msec(data->philo[i].last_ate, get_time())
			> (uint32_t) data->attr[T_DIE])
		{
			log_status(&data->philo[i], DIED, get_time());
			pthread_mutex_lock(&data->mutex[SIM_RUN]);
			data->is_running = false;
			pthread_mutex_unlock(&data->mutex[SIM_RUN]);
			return (NULL);
		}
		if (all_philo_fed(data))
		{
			log_status(&data->philo[i], ALL_FED, get_time());
			pthread_mutex_lock(&data->mutex[SIM_RUN]);
			data->is_running = false;
			pthread_mutex_unlock(&data->mutex[SIM_RUN]);
		}
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
			print_status(data->queue[i], data);
			if (data->queue[i].status == DIED
				|| data->queue[i].status == ALL_FED)
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
