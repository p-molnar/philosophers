/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 14:03:44 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/20 10:53:21 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	error_handler(int err_code)
{
	if (err_code == INVALID_INPUT)
	{
		printf("usage: ./philo ");
		printf("<philosopher count> <die duration> <eat duration> ");
		printf("<sleep duration> [<minimum eat count by each philosopher>]\n");
	}
	else if (err_code == MALLOC_ERROR)
	{
		printf ("Memory allocation failed, launch the program again\n");
		error_handler (INVALID_INPUT);
	}
	else if (err_code == MUTEX_ERROR)
	{
		printf ("Mutex error, launch the program again\n");
		error_handler (INVALID_INPUT);
	}
	else if (err_code == THREAD_ERROR)
	{
		printf ("thread error, launch the program again\n");
		error_handler (INVALID_INPUT);
	}
	return (EXIT_FAILURE);
}
