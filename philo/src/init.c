/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 20:32:56 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/22 23:16:05 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	create_philos(t_sim *data)
{
	data->philo = malloc(data->attr[N_PHILO] * sizeof(t_philo));
	if (data->philo == NULL)
		return (error_handler(MALLOC_ERR_MSG, __FILE__, __LINE__));
	return (EXIT_SUCCESS);
}

static int	create_forks(t_sim *data)
{
	data->fork = malloc(data->attr[N_PHILO] * sizeof(t_mutex));
	if (data->fork == NULL)
		return (error_handler(MALLOC_ERR_MSG, __FILE__, __LINE__));
	return (EXIT_SUCCESS);
}

int	init_simulation(t_sim *data)
{
	if (create_philos(data))
		return (EXIT_FAILURE);
	if (create_forks(data))
	{
		free (data->philo);
		return (EXIT_FAILURE);
	}
	init_mutexes(data);
	return (EXIT_SUCCESS);
}
