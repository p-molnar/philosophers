/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 13:25:32 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/20 18:58:14 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

int32_t	main(int argc, char *argv[])
{
	t_sim	data;

	if (parse_args(argc, argv, &data))
		return (EXIT_FAILURE);
	if (alloc_resources(&data))
		return (EXIT_FAILURE);
	init_resources(&data);
	if (open_semaphores(&data))
		return (EXIT_FAILURE);
	if (start_philo_processes(&data))
		return (EXIT_FAILURE);
	if (start_aux_threads(&data))
		return (EXIT_FAILURE);
	if (wait_philo_processes(&data))
		return (EXIT_FAILURE);
	if (close_semaphores(&data))
		return (EXIT_FAILURE);
	pthread_join(data.printer, NULL);
	pthread_detach(data.printer);
	return (EXIT_SUCCESS);
}
