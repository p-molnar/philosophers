/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphore.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:37:46 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/15 13:37:43 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <errno.h>
#include <string.h>

bool	semaphore_op(t_sim *data, uint8_t mode)
{
	uint16_t			i;
	const int16_t		oflag = IPC_CREAT | IPC_EXCL;
	const t_sem_attr	ht[SEM__COUNT] = {[START_LOCK] = {"/sem_start", 1}, \
								[PRINTER_LOCK] = {"/sem_print", 1}, \
								[CHECKER_LOCK] = {"/sem_checker", 1}, \
								[FORK] = {"/sem_fork", data->attr[N_PHILO]}};

	i = 0;
	while (i < SEM__COUNT)
	{
		if (mode == OPEN)
		{
			data->generic_sem[i] = sem_open(ht[i].name, \
				oflag, 0660, ht[i].init_val);
			if (data->generic_sem[i] == SEM_FAILED)
				return (thrw_err(SEM_ERR_MSG, __FILE__, __LINE__));
		}
		else if (mode == CLOSE)
			sem_close(data->generic_sem[i]);
		else if (mode == UNLINK)
			sem_unlink(ht[i].name);
		i++;
	}
	return (EXIT_SUCCESS);
}
