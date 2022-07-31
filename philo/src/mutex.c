/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 18:20:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/01 00:23:39 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

uint16_t	init_mutexes(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < MUTEX_SIZE)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL))
			return (thrw_err(MUTEX_ERR_MSG, __FILE__, __LINE__));
		i++;
	}
	i = 0;
	while (i < data->attr[N_PHILO])
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (thrw_err(MUTEX_ERR_MSG, __FILE__, __LINE__));
		if (pthread_mutex_init(&data->philo[i].self, NULL))
			return (thrw_err(MUTEX_ERR_MSG, __FILE__, __LINE__));
		i++;
	}
	return (EXIT_SUCCESS);
}

uint16_t	destroy_mutexes(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < MUTEX_SIZE)
	{
		if (pthread_mutex_destroy(&data->mutex[i]))
			return (thrw_err(MUTEX_ERR_MSG, __FILE__, __LINE__));
		i++;
	}
	i = 0;
	while (i < data->attr[N_PHILO])
	{
		if (pthread_mutex_destroy(&data->fork[i]))
			return (thrw_err(MUTEX_ERR_MSG, __FILE__, __LINE__));
		if (pthread_mutex_destroy(&data->philo[i].self))
			return (thrw_err(MUTEX_ERR_MSG, __FILE__, __LINE__));
		i++;
	}
	return (EXIT_SUCCESS);
}

void	unlock_all(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < MUTEX_SIZE)
		pthread_mutex_unlock(&data->mutex[i++]);
	i = 0;
	while (i < data->attr[N_PHILO])
	{
		pthread_mutex_unlock(&data->philo[i].self);
		pthread_mutex_unlock(&data->fork[i]);
		i++;
	}
}
