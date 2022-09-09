/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 14:06:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/06 10:21:11by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <errno.h>
#include <string.h>

static void	print_status(t_log log, sem_t *printer_lock)
{
	const char			*msg[6] = {"is thinking", "is eating", "is sleeping", \
									"has taken a fork", "died", "all fed"};

	sem_wait(printer_lock);
	printf(LOG_FMT, log.timestamp, log.philo_id, msg[log.status]);
	if (log.status == DIED)
		exit(log.status);
	sem_post(printer_lock);
}

void	log_status(t_philo *data, uint16_t status, t_time time)
{
	static u_int16_t	i;
	t_log				log;

	sem_wait(data->self);
	log.timestamp = time_delta_msec(data->sim_data->start_time, time);
	log.status = status;
	log.philo_id = data->id;
	data->sim_data->queue[i] = log;
	sem_post(data->self);
	i = (i + 1) % QUEUE__SIZE;
}

void	*child_status_printer(void *arg)
{
	uint16_t	i;
	t_sim		*data;
	int16_t		status;

	data = arg;
	i = 0;
	sem_wait(data->sem[PRINTER_LOCK]);
	sem_post(data->sem[PRINTER_LOCK]);
	while (1)
	{
		sem_wait(data->philo.self);
		status = data->queue[i].status;
		if (status != UNDEFINED)
		{
			print_status(data->queue[i], data->sem[PRINTER]);
			data->queue[i].status = UNDEFINED;
			i = (i + 1) % QUEUE__SIZE;
		}
		sem_post(data->philo.self);
		usleep(200 - data->attr[N_PHILO]);
	}
	return (NULL);
}

bool	start_aux_threads(t_sim *data)
{
	pthread_create(&data->thread[PRINTER], NULL,
		&child_status_printer, (void *)data);
	pthread_create(&data->thread[CHECKER], NULL,
		&child_status_checker, (void *)data);
	return (EXIT_SUCCESS);
}

bool	join_aux_threads(t_sim *data)
{
	pthread_join(data->thread[PRINTER], NULL);
	pthread_detach(data->thread[PRINTER]);
	pthread_join(data->thread[CHECKER], NULL);
	pthread_detach(data->thread[CHECKER]);
	return (EXIT_SUCCESS);
}
