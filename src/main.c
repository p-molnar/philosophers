/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/06 22:40:26 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/15 13:21:51 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char *argv[])
{
	t_attr	attr;
	t_philo		*philo_arr;

	philo_arr = NULL;
	if (argc < 5 || parse_input(argc, argv, &attr))
		return (error_handling(INVALID_INPUT));
	if (init_vars(&philo_arr, &attr))
		return (error_handling(MEM_ERROR));
	create_threads(philo_arr, &attr);

	return (EXIT_SUCCESS);
}
