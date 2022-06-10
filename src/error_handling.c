/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 14:03:44 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/10 12:15:58 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	error_handling(int err_code)
{
	if (err_code == INVALID_INPUT)
	{
		printf("usage: ./philo ");
		printf("<number of philosophers> <time to die> <time to eat> ");
		printf("<time to sleep> [<number of times each philosopher must eat>]\n");
	}
	else if (err_code == MEM_ERROR)
	{
		printf ("Memory allocation failed, please try again\n");
		error_handling (INVALID_INPUT);
	}
	return (EXIT_FAILURE);
}