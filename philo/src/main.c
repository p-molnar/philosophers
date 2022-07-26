/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/06 22:40:26 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/25 14:27:47 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char *argv[])
{
	t_sim	data;

	if (parse_args(argc, argv, &data))
		return (EXIT_FAILURE);
	if (init_simulation(&data))
		return (EXIT_FAILURE);
	if (init_threads(&data))
		return (EXIT_FAILURE);
	usleep(1000);
	// printf("n_philo: %i\n", data.attr[N_PHILO]);
	// printf("t_die: %i\n", data.attr[T_DIE]);
	// printf("t_eat: %i\n", data.attr[T_EAT]);
	// printf("t_sleep: %i\n", data.attr[T_SLEEP]);
	// printf("n_eat: %i\n", data.attr[N_EAT]);
	return (EXIT_SUCCESS);
}
