/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alloc.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 23:56:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/22 09:22:54 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

bool	alloc_resources(t_sim *data)
{	
	data->checker_thread = malloc(data->attr[N_PHILO] * sizeof(pthread_t));
	if (data->checker_thread == NULL)
		handle_err(MALLOC_ERR_MSG, __FILE__, __LINE__, data);
	data->child_pid_arr = malloc(data->attr[N_PHILO] * sizeof(pid_t));
	if (data->child_pid_arr == NULL)
		handle_err(MALLOC_ERR_MSG, __FILE__, __LINE__, data);
	data->philo_sem = malloc(data->attr[N_PHILO] * sizeof(sem_t *));
	if (data->philo_sem == NULL)
		handle_err(MALLOC_ERR_MSG, __FILE__, __LINE__, data);
	return (EXIT_SUCCESS);
}
