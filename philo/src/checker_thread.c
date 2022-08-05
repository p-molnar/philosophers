/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/05 13:39:17 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/05 13:48:43 by pmolnar       ########   odam.nl         */
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

static void	die_action(t_sim *data, u_int16_t i)
{
	log_status(&data->philo[i], DIED, get_time());
	pthread_mutex_lock(&data->mutex[SIM_RUN]);
	data->is_running = false;
	pthread_mutex_unlock(&data->mutex[SIM_RUN]);
}

static void	all_fed_action(t_sim *data, uint16_t i)
{
	log_status(&data->philo[i], ALL_FED, get_time());
	pthread_mutex_lock(&data->mutex[SIM_RUN]);
	data->is_running = false;
	pthread_mutex_unlock(&data->mutex[SIM_RUN]);
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
			die_action(data, i);
			return (NULL);
		}
		if (all_philo_fed(data))
		{
			all_fed_action(data, i);
			return (NULL);
		}
		i = (i + 1) % data->attr[N_PHILO];
		usleep(500);
	}
	return (NULL);
}
