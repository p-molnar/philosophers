/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 14:06:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/21 17:32:36 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <errno.h>
#include <string.h>

void	print_status(uint8_t status, t_time curr_time, t_philo *philo_data)
{
	const char			*msg[6] = {"is thinking", "is eating", "is sleeping", \
									"has taken a fork", "died", "all fed"};
	uint32_t			ts;

	sem_wait(philo_data->sim_data->generic_sem[PRINTER_LOCK]);
	ts = time_delta_msec(philo_data->sim_data->start_time, curr_time);
	printf(LOG_FMT, ts, philo_data->id, msg[status]);
	if (status == DIED)
		exit(status);
	sem_post(philo_data->sim_data->generic_sem[PRINTER_LOCK]);
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
