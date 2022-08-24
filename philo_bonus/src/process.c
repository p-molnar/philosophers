/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 14:01:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/24 18:53:45 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <errno.h>
#include <string.h>

bool	start_philo_processes(t_sim *data)
{
	uint16_t	i;
	int32_t		pid;

	data->philo_pid = malloc(data->attr[N_PHILO] * sizeof(uint32_t));
	if (data->philo_pid == NULL)
		thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__);
	sem_wait(data->sem[START_LOCK]);
	i = 0;
	while (i < data->attr[N_PHILO])
	{
		pid = fork();
		if (pid == -1)
			return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
		else if (pid == 0)
		{
			start_aux_threads(data);
			simulate(&(data->philo[i]));
			join_aux_threads(data);
			exit(EXIT_SUCCESS);
		}
		data->philo_pid[i] = pid;
		i++;
	}
	sem_post(data->sem[START_LOCK]);	
	return (EXIT_SUCCESS);
}

bool	wait_philo_processes(t_sim *data)
{	
	uint16_t	i;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		if (waitpid(data->philo_pid[i], NULL, 0) == -1)
		{
			printf("error: %s\n", strerror(errno));
			thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
