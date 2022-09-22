/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thrw_err.c                                    		:+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 14:03:44 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/22 20:23:08 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <stdio.h>

uint16_t	handle_err(char *msg, char *file_name, int line_no, t_sim *data)
{
	printf("%s:	%s:%d\n", msg, file_name, line_no);
	printf(USAGE_MSG);
	if (data)
	{
		kill_all_child_process(data);
		clean_up(data);
	}
	exit (EXIT_FAILURE);
}
