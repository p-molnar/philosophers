/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/06 22:40:26 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/26 13:50:45 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char *argv[])
{
	t_sim	data;

	if (parse_args(argc, argv, &data))
		return (EXIT_FAILURE);
	if (alloc_sim_resources(&data))
		return (EXIT_FAILURE);
	if (init_mutexes(&data))
		return (EXIT_FAILURE);
	if (create_threads(&data))
		return (EXIT_FAILURE);
	if (join_threads(&data))
		return (EXIT_FAILURE);
	if (destroy_mutexes(&data))
		return (EXIT_FAILURE);
	free (data.philo);
	free (data.fork);
	printf("n_philo: %i\n", data.attr[N_PHILO]);
	printf("t_die: %i\n", data.attr[T_DIE]);
	printf("t_eat: %i\n", data.attr[T_EAT]);
	printf("t_sleep: %i\n", data.attr[T_SLEEP]);
	printf("n_eat: %i\n", data.attr[N_EAT]);
	return (EXIT_SUCCESS);
}
