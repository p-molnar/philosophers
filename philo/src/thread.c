/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 17:38:50 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/01 00:18:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

uint16_t	create_threads(t_sim *data)
{
	uint16_t	i;

	pthread_mutex_lock(&data->mutex[UTIL_START]);
	if (pthread_create(&data->thread[CHECKER], NULL, checker, data))
		return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
	if (pthread_create(&data->thread[PRINTER], NULL, printer, data))
		return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
	pthread_mutex_lock(&data->mutex[INIT]);
	i = 0;
	while (i < data->attr[N_PHILO])
	{
		if (pthread_create(&data->philo[i].thread, NULL, simulation, \
							&data->philo[i]))
		{
			return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
		}
		i++;
	}
	data->start_time = get_time();
	pthread_mutex_unlock(&data->mutex[INIT]);
	return (EXIT_SUCCESS);
}

uint16_t	join_threads(t_sim *data)
{
	uint16_t	i;

	if (pthread_join(data->thread[CHECKER], NULL))
		return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
	if (pthread_join(data->thread[PRINTER], NULL))
		return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
	i = 0;
	while (i < data->attr[N_PHILO])
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
		i++;
	}
	return (EXIT_SUCCESS);
}
