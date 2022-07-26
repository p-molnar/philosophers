/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 17:38:50 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/25 19:55:25 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	init_util_threads(t_sim *data)
{
	pthread_mutex_lock(&data->mutex[START]);
	if (pthread_create(&data->thread[CHECKER], NULL, \
		(void *)&checker, (void *)&data))
	{
		return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
	}
	pthread_mutex_unlock(&data->mutex[START]);
	pthread_mutex_lock(&data->mutex[START]);
	if (pthread_create(&data->thread[PRINTER], NULL, \
		(void *)&printer, (void *)&data))
	{
		return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
	}
	pthread_mutex_unlock(&data->mutex[START]);
	return (EXIT_SUCCESS);
}

static int	init_philo_threads(t_sim *data)
{
	uint16_t	i;

	i = 0;
	pthread_mutex_lock(&data->mutex[START]);
	while (i < data->attr[N_PHILO])
	{
		if (pthread_create(&data->philo[i].thread, NULL, \
			(void *)&simulation, (void *)&data->philo[i]))
		{
			return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
		}
		i++;
	}
	usleep(1000);
	pthread_mutex_unlock(&data->mutex[START]);
	return (EXIT_SUCCESS);
}

int	init_threads(t_sim *data)
{
	if (init_util_threads(data))
		return (EXIT_FAILURE);
	if (init_philo_threads(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
