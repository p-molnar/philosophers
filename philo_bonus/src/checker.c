/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/05 13:39:17 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/22 10:30:33 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <pthread.h>
#include <unistd.h>

void	*child_status_checker(void *arg)
{	
	t_sim		*data;
	uint32_t	t_delta;

	data = arg;
	sem_wait(data->generic_sem[CHECKER_LOCK]);
	sem_post(data->generic_sem[CHECKER_LOCK]);
	while (1)
	{
		t_delta = time_delta_msec(data->philo.last_ate, get_time());
		if (t_delta > (uint32_t) data->attr[T_DIE])
			print_status(DIED, get_time(), &data->philo);
		usleep(200 - data->attr[N_PHILO]);
	}
	return (NULL);
}

bool	start_aux_threads(t_sim *data)
{
	pthread_create(&data->thread[CHECKER], NULL,
		&child_status_checker, (void *)data);
	return (EXIT_SUCCESS);
}

bool	join_aux_threads(t_sim *data)
{
	pthread_join(data->thread[CHECKER], NULL);
	pthread_detach(data->thread[CHECKER]);
	return (EXIT_SUCCESS);
}
