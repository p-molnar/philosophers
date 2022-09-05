/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 14:06:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/05 19:59:39 by pmolnar       ########   odam.nl         */
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
	i = (i + 1) % QUEUE__SIZE;
	sem_post(data->self);
}

void	*printer_thread(void *arg)
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
		sem_post(data->philo.self);
		if (status != UNDEFINED)
		{
			print_status(data->queue[i], data->sem[PRINTER]);
			sem_wait(data->philo.self);
			data->queue[i].status = UNDEFINED;
			i = (i + 1) % QUEUE__SIZE;
			sem_post(data->philo.self);
		}
		usleep(500);
	}
	return (NULL);
}

bool	start_aux_threads(t_sim *data)
{
	pthread_create(&data->thread[PRINTER], NULL, &printer_thread, (void *)data);
	pthread_create(&data->thread[CHECKER], NULL, &checker_thread, (void *)data);
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
