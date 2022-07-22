/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 18:20:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/22 22:39:28 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	init_mutexes(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < MUTEX_SIZE)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL))
			return (error_handler(MUTEX_ERR_MSG, __FILE__, __LINE__));
		i++;
	}
	i = 0;
	while (i < data->attr[N_PHILO])
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (error_handler(MUTEX_ERR_MSG, __FILE__, __LINE__));
		i++;
	}
	return (EXIT_SUCCESS);
}
