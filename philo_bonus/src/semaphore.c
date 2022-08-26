/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphore.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:37:46 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/26 16:33:05 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <errno.h>
#include <string.h>

bool	semaphore_op(t_sim *data, uint8_t mode)
{
	uint16_t			i;
	const int16_t		oflag = IPC_CREAT | IPC_EXCL;
	const t_sem_attr	ht[SEM__COUNT] = {{"/sem_start", 1}, \
						{"/sem_print", 1}, {"/sem_checker", 1}, \
						{"/sem_fork", data->attr[N_PHILO]}, \
						{"/sem_log_rw", 1}, {"sem_queue_rw", 1},
						{"/sem_die", 1}};

	i = 0;
	while (i < SEM__COUNT)
	{
		if (mode == OPEN)
		{
			data->sem[i] = sem_open(ht[i].name, oflag, 0660, ht[i].init_val);
			if (data->sem[i] == SEM_FAILED)
				return (thrw_err(SEM_ERR_MSG, __FILE__, __LINE__));
		}
		else if (mode == CLOSE)
		{
			if (sem_close(data->sem[i]) == -1)
				return (thrw_err(SEM_ERR_MSG, __FILE__, __LINE__));
		}
		else if (mode == UNLINK)
		{
			sem_unlink(ht[i].name);
				// return (thrw_err(SEM_ERR_MSG, __FILE__, __LINE__));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
