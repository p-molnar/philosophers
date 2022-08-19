/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 16:51:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/19 22:35:39 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

bool	simulate(t_philo *philo)
{
	sem_wait(philo->sim_data->sem[START_LOCK]);
	sem_post(philo->sim_data->sem[START_LOCK]);
	printf("id: %d\n", philo->id);
	return (EXIT_SUCCESS);
}
