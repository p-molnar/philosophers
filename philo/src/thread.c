/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 17:38:50 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/26 22:53:18 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static uint16_t	create_util_threads(t_sim *data)
{
	if (pthread_create(&data->thread[CHECKER], NULL, \
		(void *)checker, (void *)data))
	{
		return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
	}
	if (pthread_create(&data->thread[PRINTER], NULL, \
		(void *)printer, (void *)data))
	{
		return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
	}
	return (EXIT_SUCCESS);
}

static uint16_t	create_philo_threads(t_sim *data)
{
	uint16_t	i;

	i = 0;
	pthread_mutex_lock(&data->mutex[INIT]);
	while (i < data->attr[N_PHILO])
	{
		if (pthread_create(&data->philo[i].thread, NULL, \
			(void *)simulation, &data->philo[i]))
		{
			return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
		}
		i++;
	}
	data->start_time = get_time();
	precise_sleep(1);
	pthread_mutex_unlock(&data->mutex[INIT]);
	return (EXIT_SUCCESS);
}

static uint16_t	join_util_threads(t_sim *data)
{
	(void) data;
	if (pthread_join(data->thread[CHECKER], NULL))
		return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
	if (pthread_join(data->thread[PRINTER], NULL))
		return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
	return (EXIT_SUCCESS);
}

uint16_t	join_philo_threads(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (thrw_err(THREAD_ERR_MSG, __FILE__, __LINE__));
		i++;
	}
	return (EXIT_SUCCESS);

}

uint16_t	create_threads(t_sim *data)
{
	if (create_util_threads(data))
		return (EXIT_FAILURE);
	if (create_philo_threads(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

uint16_t	join_threads(t_sim *data)
{
	if (join_util_threads(data))
		return (EXIT_FAILURE);
	if (join_philo_threads(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}