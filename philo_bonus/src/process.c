/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 14:01:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/30 16:20:28 by pmolnar       ########   odam.nl         */
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
		data->pid_arr[i] = fork();
		if (data->pid_arr[i] == -1)
			return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
		else if (data->pid_arr[i] == 0)
		{
			// printf("id: %d, pid: %d\n", i + 1, getpid());
			init_philo(data, i);
			start_aux_threads(data);
			simulate(&data->philo);
			join_aux_threads(data);
			// return(data->philo.status);
			printf("philo status: %d\n", data->philo.status);
			exit(data->philo.status);
		}
		i++;
	}
	sem_post(data->sem[START_LOCK]);
	sem_post(data->sem[PRINTER_LOCK]);
	precise_msleep(1);
	sem_post(data->sem[CHECKER_LOCK]);
	return (EXIT_SUCCESS);
}


void	kill_all_child_process(t_sim *data, bool *philo_exited)
{
	uint16_t	i;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		if (philo_exited[i] == false)
		{
			if (kill(data->pid_arr[i], SIGKILL) == -1)
				printf("kill error: %s\n", strerror(errno));
			// printf("kill: %d\n", data->philo_pid[i]);
		}
		i++;
	}
}

bool	wait_child_processes(t_sim *data)
{	
	uint16_t	i;
	int16_t		pid;
	int			status;
	int			fed_philo_count;

	fed_philo_count = 0;
	i = 0;
	while (1)
	{
		if (data->philo_exited[i] == false)
		{
			pid = waitpid(data->pid_arr[i], &status, WNOHANG);
			// printf("checking: %d, status: %d\n", data->philo_pid[i], status);
			if (pid == -1)
			{
				printf("error: %s\n", strerror(errno));
				return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
			}
			else if (WIFEXITED(status) && WEXITSTATUS(status) == FED)
			{
				printf("philo %d exited\n", i + 1);
				data->philo_exited[i] = true;
				fed_philo_count++;
				if (fed_philo_count == data->attr[N_PHILO])
					kill_all_child_process(data, data->philo_exited);
			}
			if (WIFEXITED(status) && WEXITSTATUS(status) == DIED)
			{
				printf("killing all\n");
				kill_all_child_process(data, data->philo_exited);
				return (EXIT_SUCCESS);
			}
		}
		usleep(500);
		i = (i + 1) % data->attr[N_PHILO];
	}
	return (EXIT_SUCCESS);
}
