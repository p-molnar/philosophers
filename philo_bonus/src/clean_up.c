/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 09:39:06 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/23 09:09:45 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

void	clean_up(t_sim *data)
{
	free(data->checker_thread);
	free(data->child_pid_arr);
	free(data->philo_sem);
}
