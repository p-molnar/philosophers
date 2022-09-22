/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 13:25:32 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/22 09:39:36 by pmolnar       ########   odam.nl         */
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
	if (semaphore_op(&data, UNLINK))
		return (EXIT_FAILURE);
	if (semaphore_op(&data, OPEN))
		return (EXIT_FAILURE);
	create_child_processes(&data);
	if (wait_and_check_child_processes(&data))
		return (EXIT_FAILURE);
	if (semaphore_op(&data, CLOSE))
		return (EXIT_FAILURE);
	clean_up(&data);
	return (EXIT_SUCCESS);
}
