/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphore.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:37:46 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/19 23:16:02 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <errno.h>
#include <string.h>

const char	*g_sem_name[SEM__COUNT] = {"/sem_start"};

bool	open_semaphores(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < SEM__COUNT)
	{
		data->sem[i] = sem_open(g_sem_name[i], IPC_CREAT, 0660, 1);
		if (data->sem[i] == SEM_FAILED)
			return (thrw_err(SEM_ERR_MSG, __FILE__, __LINE__));
		i++;
	}
	return (EXIT_SUCCESS);
}

bool	close_semaphores(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < SEM__COUNT)
	{
		if (sem_unlink(g_sem_name[i]) == -1)	
			return (thrw_err(SEM_ERR_MSG, __FILE__, __LINE__));
		if (sem_close(data->sem[i]) == -1)
			return (thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__));
		i++;
	}
	return (EXIT_SUCCESS);
}
