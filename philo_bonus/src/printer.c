/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 14:06:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/24 22:22:29 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <errno.h>
#include <string.h>

static void	print_status(t_log log, t_sim *data)
{
	const char			*msg[6] = {"is thinking", "is eating", "is sleeping", \
									"has taken a fork", "died", "all fed"};
	uint16_t			i;

	if (log.status == ALL_FED)
	{
		printf("\n%-d all philosophers have eaten\n", log.timestamp);
		printf("\n-----   SUMMARY   -----\n");
		i = 0;
		while (i < data->attr[N_PHILO])
		{
			// pthread_mutex_lock(&data->philo[i].self);
			printf("philo %d %s: %d time(s)\n", data->philo[i].id, "ate",
				data->philo[i].eat_count);
			// pthread_mutex_unlock(&data->philo[i].self);
			i++;
		}
		printf("-----------------------\n");
	}
	else
		printf(LOG_FMT, log.timestamp, log.philo_id, msg[log.status]);
}

void	log_status(t_philo *data, uint16_t status, t_time time)
{
	static u_int16_t	i;
	t_log				log;

	// if(sem_wait(data->sim_data->sem[LOG_RW]) == -1)
	// {
	// 	printf("error printer: %s\n", strerror(errno));
	// }
	// printf("somethings happening: %d\n", __LINE__);
	log.timestamp = time_delta_msec(data->sim_data->start_time, time);
	log.status = status;
	log.philo_id = data->id;
	// sem_wait(data->sim_data->sem[QUEUE_RW]);
	data->sim_data->queue[i] = log;
	// printf("process: %ld, %d\n", data->sim_data->start_time.tv_sec, data->sim_data->start_time.tv_usec);
	// printf("philo %d, new = %d\n", data->id, *data->sim_data->new);
	// printf("%d, %d, %c\n", log.timestamp, log.philo_id, "TES"[log.status]);
	i = (i + 1) % QUEUE__SIZE;
	// sem_post(data->sim_data->sem[QUEUE_RW]);
	// sem_post(data->sim_data->sem[LOG_RW]);
}

void	*printer_thread(void *arg)
{
	uint16_t	i;
	t_sim		*data;

	data = arg;
	i = 0;
	while (true)
	{
		// sem_wait(data->sem[QUEUE_RW]);
		if (data->queue[i].status != UNDEFINED)
		{
			print_status(data->queue[i], data);
			if (data->queue[i].status == DIED
				|| data->queue[i].status == ALL_FED)
			{
				// unlock_all(data);
				return (NULL);
			}
			data->queue[i].status = UNDEFINED;
			i = (i + 1) % QUEUE__SIZE;
		}
		// sem_post(data->sem[QUEUE_RW]);
		usleep(500);
	}
	return (NULL);
}

bool	start_aux_threads(t_sim *data)
{
	// sem_wait(data->sem[PRINTER_LOCK]);
	pthread_create(&data->thread[PRINTER], NULL, &printer_thread, (void *)data);
	pthread_create(&data->thread[CHECKER], NULL, &checker_thread, (void *)data);
	// sem_post(data->sem[PRINTER_LOCK]);
	return (EXIT_SUCCESS);
}

bool	join_aux_threads(t_sim *data)
{
	// sem_wait(data->sem[PRINTER_LOCK]);
	pthread_join(data->thread[PRINTER], NULL);
	pthread_detach(data->thread[PRINTER]);
	pthread_join(data->thread[CHECKER], NULL);
	pthread_detach(data->thread[CHECKER]);
	// sem_post(data->sem[PRINTER_LOCK]);
	return (EXIT_SUCCESS);
}