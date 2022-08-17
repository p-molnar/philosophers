/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 20:58:51 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/17 22:52:29 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <errno.h>
#include <string.h>
#include <sys/shm.h>

void	init_resources(t_sim *data)
{	
	uint16_t	i;
	uint16_t	n_philo;
	int			*sval;

	n_philo = data->attr[N_PHILO];
	i = 0;
	data->is_running = true;
	while (i < n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].sim_data = data;
		i++;
	}
	i = 0;
	while (i < QUEUE_SIZE)
		data->queue[i++].status = UNDEFINED;
	i = 0;
	while (i < SEM_SIZE)
	{
		sem_unlink("/1");
		data->sem[i] = sem_open("/1", IPC_CREAT, 0660, 0);
		if (data->sem[i] == SEM_FAILED)
		{
			printf("error: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		sem_getvalue(data->sem[i], sval);
		printf("sem_val: %d\n", *sval);
		i++;
	}
}
