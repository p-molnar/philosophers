/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 14:01:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/09 14:13:30 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void	lock_action(t_sim *data, uint16_t action)
{
	if (action == LOCK)
	{
		sem_wait(data->sem[START_LOCK]);
		sem_wait(data->sem[PRINTER_LOCK]);
		sem_wait(data->sem[CHECKER_LOCK]);
	}
	else if (action == UNLOCK)
	{
		sem_post(data->sem[START_LOCK]);
		sem_post(data->sem[PRINTER_LOCK]);
		usleep(1000);
		sem_post(data->sem[CHECKER_LOCK]);
	}
}

bool	create_child_processes(t_sim *data)
{
	uint16_t	i;

	lock_action(data, LOCK);
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
		i++;
	}
	lock_action(data, UNLOCK);
	return (EXIT_SUCCESS);
}

void	kill_all_child_process(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		kill(data->child_pid_arr[i], SIGKILL);
		i++;
	}
}

uint16_t	check_exit_status(int status, t_sim *data)
{
	static uint16_t	fed_philo_count;

	if (WEXITSTATUS(status) == FED)
	{
		fed_philo_count++;
		if (fed_philo_count == data->attr[N_PHILO])
		{
			printf("All philos have eaten at least %d time(s)\n",
				data->attr[N_EAT]);
			return (ALL_FED);
		}
		return (FED);
	}
	else if (WEXITSTATUS(status) == DIED)
	{
		kill_all_child_process(data);
		return (DIED);
	}
	return (EXIT_SUCCESS);
}

bool	wait_child_processes(t_sim *data)
{	
	uint16_t	i;
	uint16_t	exit_status;
	int			status;

	i = 0;
	sem_wait(data->sem[START_LOCK]);
	sem_post(data->sem[START_LOCK]);
	while (1)
	{
		while (data->child_pid_arr[i]
			!= waitpid(data->child_pid_arr[i], &status, WNOHANG))
		{
			i = (i + 1) % data->attr[N_PHILO];
		}
		exit_status = check_exit_status(status, data);
		if (exit_status == DIED || exit_status == ALL_FED)
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
