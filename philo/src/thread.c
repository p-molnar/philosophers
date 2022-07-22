/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 17:38:50 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/22 23:38:31 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	init_philo_threads(t_sim *data)
{
	uint16_t		i;
	t_thread_data	thread_data;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		thread_data.data = data;
		thread_data.philo = &data->philo[i];
		if (pthread_create(&data->philo[i].thread, NULL, \
			(void *)&simulation, (void *)&thread_data))
		{
			return (error_handler(THREAD_ERR_MSG, __FILE__, __LINE__));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_threads(t_sim *data)
{
	if (init_philo_threads(data))
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
