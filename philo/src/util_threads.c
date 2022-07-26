/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_threads.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 14:06:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/25 14:30:15 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	checker(t_sim *data)
{
	(void) data;
	printf("checker started\n");
	return (EXIT_SUCCESS);
}

int	printer(t_sim *data)
{
	(void) data;
	printf("printer started\n");
	return (EXIT_SUCCESS);
}
