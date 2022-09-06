/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alloc.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 23:56:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/06 10:59:24 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

bool	alloc_resources(t_sim *data)
{	
	data->checker_thread = malloc(data->attr[N_PHILO] * sizeof(pthread_t));
	if (data->checker_thread == NULL)
		thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__);
	data->pid_arr = malloc(data->attr[N_PHILO] * sizeof(uint32_t));
	if (data->pid_arr == NULL)
		thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__);
	data->philo_exited = malloc(data->attr[N_PHILO] * sizeof(bool));
	if (data->philo_exited == NULL)
		return (thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__));
	return(EXIT_SUCCESS);
}
