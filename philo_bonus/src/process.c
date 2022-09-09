/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 14:01:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/09 11:59:35by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

bool	create_child_processes(t_sim *data)
{
	uint16_t	i;

	sem_wait(data->sem[START_LOCK]);
	sem_wait(data->sem[CHECKER_LOCK]);
	sem_wait(data->sem[PRINTER_LOCK]);
	i = 0;
	while (i < data->attr[N_PHILO])
	{
		data->child_pid_arr[i] = fork();
		if (data->child_pid_arr[i] < 0)
			return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
		else if (data->child_pid_arr[i] == 0)
		{
			init_philo(data, i);
			start_aux_threads(data);
			simulate(&data->philo);
			join_aux_threads(data);
			exit(EXIT_SUCCESS);
		}
		printf("philo[%d]_pid: %d\n", i, data->child_pid_arr[i]);
		i++;
	}
	sem_post(data->sem[START_LOCK]);
	sem_post(data->sem[PRINTER_LOCK]);
	precise_msleep(1);
	sem_post(data->sem[CHECKER_LOCK]);
	return (EXIT_SUCCESS);
}

void	kill_all_child_process(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		printf("killing: %d\n", i);
		kill(data->child_pid_arr[i], SIGKILL);
		i++;
	}
}

bool	wait_child_processes(t_sim *data)
{	
	uint16_t	i;
	pid_t		pid;
	int			status;
	int			fed_philo_count;

	fed_philo_count = 0;
	i = 0;
	sem_wait(data->sem[START_LOCK]);
	sem_post(data->sem[START_LOCK]);
	printf("preloop\n");
	pid = waitpid(data->child_pid_arr[i], &status, 0);
	printf("pid: %d\n", pid);
	while (pid != data->child_pid_arr[i])
	{
		printf("enters loop?\n");
		i = (i + 1) % data->attr[N_PHILO];
		pid = waitpid(data->child_pid_arr[i], &status, 0);
	}
	printf("postloop\n");
	printf("exited: %d\n", data->child_pid_arr[i]);
	if (waitpid(data->child_pid_arr[i], &status, 0) == -1)
	{
		printf("error: %s\n", strerror(errno));
		return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
	}
	if (WEXITSTATUS(status) == FED)
	{
		fed_philo_count++;
		if (fed_philo_count == data->attr[N_PHILO])
		{
			printf("All philos have eaten\n");
			kill_all_child_process(data);
			return (EXIT_SUCCESS);
		}
	}
	else if (WEXITSTATUS(status) == DIED)
	{
		printf("killing all\n");
		kill_all_child_process(data);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
