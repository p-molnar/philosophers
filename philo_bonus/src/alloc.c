/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alloc.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 11:35:56 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/20 13:36:03 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

bool	alloc_resources(t_sim *data)
{
	data->philo = malloc(data->attr[N_PHILO] * sizeof(t_philo));
	if (data->philo == NULL)
		return (thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__));
	return (EXIT_SUCCESS);
}