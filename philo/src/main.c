/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/06 22:40:26 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/21 19:19:03 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char *argv[])
{
	t_sim_data	attr;
	t_philo		*philo_arr;

	philo_arr = NULL;
	if (argc == 5 || argc == 6)
	{
		if (parse_args(argc, argv, &attr))
			return (EXIT_FAILURE);
	}
	else
		return (error_handler(INVALID_INPUT, NULL));
	return (EXIT_SUCCESS);
}
