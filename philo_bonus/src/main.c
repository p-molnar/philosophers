/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 13:25:32 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/11 22:25:38 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

int32_t	main(int argc, char *argv[])
{
	t_sim	data;

	if (parse_args(argc, argv, &data))
		return (EXIT_FAILURE);
	init_resources(&data);
	// if (init_processes(&data))
	// 	return (EXIT_FAILURE);
	// if (init_aux_threads(&data))
	// 	return (EXIT_FAILURE);
	// if (start_simulate(&data))
	// 	return (EXIT_FAILURE);
	// if (clean_up(&data))
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
