/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/06 22:40:26 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/22 01:22:04 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char *argv[])
{
	t_data	data;

	if (parse_args(argc, argv, &data))
		return (EXIT_FAILURE);
	if ()
	printf("n_philo: %i\n", data.arg[N_PHILO]);
	printf("t_die: %i\n", data.arg[T_DIE]);
	printf("t_eat: %i\n", data.arg[T_EAT]);
	printf("t_sleep: %i\n", data.arg[T_SLEEP]);
	printf("n_eat: %i\n", data.arg[N_EAT]);
	return (EXIT_SUCCESS);
}
