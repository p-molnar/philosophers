/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/06 22:40:26 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/29 12:03:19 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	free_all(t_sim *data)
{
	if (data->fork)
		free(data->fork);
	if (data->philo)
		free(data->philo);
}

void	clean_up(t_sim *data)
{
	unlock_all(data);
	free_all(data);
}

int	main(int argc, char *argv[])
{
	t_sim	data;

	if (parse_args(argc, argv, &data))
		return (2);
	if (alloc_sim_resources(&data))
		return (3);
	init_resources(&data);
	if (init_mutexes(&data))
		return (5);
	if (create_threads(&data))
		return (6);
	if (join_threads(&data))
		return (7);
	if (destroy_mutexes(&data))
		return (8);
	free_all(&data);
	// printf("n_philo: %i\n", data.attr[N_PHILO]);
	// printf("t_die: %i\n", data.attr[T_DIE]);
	// printf("t_eat: %i\n", data.attr[T_EAT]);
	// printf("t_sleep: %i\n", data.attr[T_SLEEP]);
	// printf("n_eat: %i\n", data.attr[N_EAT]);
	return (EXIT_SUCCESS);
}
