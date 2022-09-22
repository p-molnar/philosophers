/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 09:39:06 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/22 09:40:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

void	clean_up(t_sim *data)
{
	if (data->checker_thread)
		free(data->checker_thread);
	if (data->child_pid_arr)
		free(data->child_pid_arr);
	if (data->philo_sem)
		free(data->philo_sem);
}
