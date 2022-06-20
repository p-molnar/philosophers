/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/06 22:40:26 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/20 09:42:57 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char *argv[])
{
	t_attr	attr;
	t_philo	*philo_arr;

	philo_arr = NULL;
	if (argc == 5 || argc == 6)
	{
		if (parse_args(argc, argv, &attr))
			return (EXIT_FAILURE);
		if (set_up_simulation(&philo_arr, &attr))
			return (EXIT_FAILURE);
		if (launch_simulation(philo_arr, &attr))
			return (EXIT_FAILURE);
		// system("leaks philo");
	}
	else
		return (error_handler(INVALID_INPUT));
	return (EXIT_SUCCESS);
}
