/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alloc.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 11:35:56 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/12 11:39:38 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

bool	alloc_resources(t_sim *data)
{
	uint16_t	n_philo;

	n_philo = data->attr[N_PHILO];
	data->philo = malloc(n_philo * sizeof(t_philo));
	if (data->philo == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}