/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 14:01:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/25 20:26:21 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

bool	create_child_processes(t_sim *data)
{
	uint16_t	i;
	int32_t		pid;

	data->philo_pid = malloc(data->attr[N_PHILO] * sizeof(uint32_t));
	if (data->philo_pid == NULL)
		thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__);
	sem_wait(data->sem[START_LOCK]);
	sem_wait(data->sem[CHECKER_LOCK]);
	sem_wait(data->sem[PRINTER_LOCK]);
	i = 0;
	while (i < data->attr[N_PHILO])
	{
		pid = fork();
		if (pid == -1)
			return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
		else if (pid == 0)
		{
			init_philo(data, i + 1);
			start_aux_threads(data);
			simulate(&data->philo);
			join_aux_threads(data);
			exit(data->philo.status);
		}
		data->philo_pid[i] = pid;
		i++;
	}
	sem_post(data->sem[START_LOCK]);
	sem_post(data->sem[PRINTER_LOCK]);
	precise_usleep(data->attr[N_PHILO]);
	sem_post(data->sem[CHECKER_LOCK]);
	return (EXIT_SUCCESS);
}


void	kill_all_child_process(t_sim *data, uint16_t except)
{
	uint16_t	i;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		if (i != except)
		{
			if (kill(data->philo_pid[i], SIGKILL) == -1)
				printf("kill error: %s\n", strerror(errno));
			printf("kill: %d\n", data->philo_pid[i]);
		}
		i++;
	}
}

bool	wait_philo_processes(t_sim *data)
{	
	uint16_t	i;
	int			status;

	i = 0;
	while (1)
	{
		// printf("checking: %d\n", data->philo_pid[i]);
		if (waitpid(data->philo_pid[i], &status, WNOHANG) == -1)
			return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
		else if (WEXITSTATUS(status) == DIED)
		{
			kill_all_child_process(data, i);
			return (EXIT_SUCCESS);
		}
		i = (i + 1) % data->attr[N_PHILO];
	}
	return (EXIT_SUCCESS);
}
