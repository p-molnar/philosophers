/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 14:01:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/19 23:01:14 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

bool	start_philo_processes(t_sim *data)
{
	uint16_t	i;

	i = 0;
	data->philo_pid = malloc(data->attr[N_PHILO] * sizeof(uint32_t));
	if (data->philo_pid == NULL)
		thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__);
	sem_wait(data->sem[START_LOCK]);
	while (i < (uint32_t)data->attr[N_PHILO])
	{
		data->philo_pid[i] = fork();
		if (data->philo_pid[i] == 0)
		{
			simulate(&data->philo[i]);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	data->start_time = get_time();
	sem_post(data->sem[START_LOCK]);
	return (EXIT_SUCCESS);
}

#include <errno.h>
#include <string.h>

bool	wait_philo_processes(t_sim *data)
{	
	uint16_t	i;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		if (waitpid(data->philo_pid[i], NULL, 0) == -1)
		{
			printf("%s\n", strerror(errno));
			thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
