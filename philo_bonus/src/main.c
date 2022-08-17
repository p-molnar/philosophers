/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 13:25:32 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/17 22:46:26 by pmolnar       ########   odam.nl         */
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
	if (start_processes(&data))
		return (EXIT_FAILURE);
	sem_unlink("/1");
	sem_close(data.sem[SEM_START]);
	// if (start_aux_threads(&data))
	// 	return (EXIT_FAILURE);
	// if (start_simulate(&data))
	// 	return (EXIT_FAILURE);
	// if (clean_up(&data))
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
