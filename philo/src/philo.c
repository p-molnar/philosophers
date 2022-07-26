/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 21:20:35 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/26 17:19:38 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	p_think(t_philo *data)
{
	(void) data;
}

void	p_eat(t_philo *data)
{
	(void) data;
}

void	p_sleep(t_philo *data)
{
	(void) data;
}

int	simulation(t_philo *philo)
{
	pthread_mutex_lock(philo->m);
	printf("philo id: %d\n", philo->id);
	pthread_mutex_unlock(philo->m);
	// while (true)
	// {
	// 	p_think(data);
	// 	p_eat(data);
	// 	p_sleep(data);
	// }
	return (EXIT_SUCCESS);
}
