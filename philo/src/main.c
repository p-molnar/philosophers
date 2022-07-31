/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/06 22:40:26 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/01 00:31:58 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char *argv[])
{
	t_sim	data;

	if (parse_args(argc, argv, &data))
		return (EXIT_SUCCESS);
	if (alloc_sim_resources(&data))
		return (EXIT_SUCCESS);
	init_resources(&data);
	if (init_mutexes(&data))
		return (EXIT_SUCCESS);
	if (create_threads(&data))
		return (EXIT_SUCCESS);
	if (join_threads(&data))
		return (EXIT_SUCCESS);
	if (destroy_mutexes(&data))
		return (EXIT_SUCCESS);
	free_all(&data);
	return (EXIT_SUCCESS);
}
