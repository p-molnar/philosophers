/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_threads.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/25 14:06:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/26 22:59:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

uint16_t	checker(t_sim *data)
{
	(void) data;
	printf("checker started\n");
	return (EXIT_SUCCESS);
}

uint16_t	printer(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (data->is_running)
	{
		if (data->queue[i].status != UNDEFINED)
		{
			print_status(data->queue[i]);
			if (++i == QUEUE_SIZE)
				i = 0;
		}
		usleep(500);
	}
	return (EXIT_SUCCESS);
}
