/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphore.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:37:46 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/20 18:53:09 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <errno.h>
#include <string.h>

bool	open_semaphores(t_sim *data)
{
	uint16_t	n_philo;

	n_philo = data->attr[N_PHILO];
	data->sem[START_LOCK] = sem_open("/sem_start", IPC_CREAT, 0660, 1);
	data->sem[PRINTER_LOCK] = sem_open("/sem_print", IPC_CREAT, 0660, 1);
	data->sem[FORK] = sem_open("/sem_fork", IPC_CREAT, 0660, n_philo);
	data->sem[LOG_RW] = sem_open("/sem_log_rw", IPC_CREAT, 0660, 5);
	data->sem[QUEUE_RW] = sem_open("/sem_queue_rw", IPC_CREAT, 0660, 1);
	if (data->sem[START_LOCK] == SEM_FAILED
		|| data->sem[PRINTER_LOCK] == SEM_FAILED
		|| data->sem[FORK] == SEM_FAILED
		|| data->sem[LOG_RW] == SEM_FAILED
		|| data->sem[QUEUE_RW] == SEM_FAILED)
	{
		return (thrw_err(SEM_ERR_MSG, __FILE__, __LINE__));
	}
	return (EXIT_SUCCESS);
}

bool	close_semaphores(t_sim *data)
{
	if (sem_unlink("/sem_start") == -1)
		return (thrw_err(SEM_ERR_MSG, __FILE__, __LINE__));
	if (sem_unlink("/sem_fork") == -1)
		return (thrw_err(SEM_ERR_MSG, __FILE__, __LINE__));
	if (sem_unlink("/sem_print") == -1)
		return (thrw_err(SEM_ERR_MSG, __FILE__, __LINE__));
	if (sem_unlink("/sem_log_rw") == -1)
		return (thrw_err(SEM_ERR_MSG, __FILE__, __LINE__));
	if (sem_unlink("/sem_queue_rw") == -1)
		return (thrw_err(SEM_ERR_MSG, __FILE__, __LINE__));
	if (sem_close(data->sem[START_LOCK]) == -1)
		return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
	if (sem_close(data->sem[PRINTER_LOCK]) == -1)
		return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
	if (sem_close(data->sem[FORK]) == -1)
		return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
	if (sem_close(data->sem[LOG_RW]) == -1)
		return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
	if (sem_close(data->sem[QUEUE_RW]) == -1)
		return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
	return (EXIT_SUCCESS);
}
