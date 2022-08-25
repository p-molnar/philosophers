/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thrw_err.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 14:03:44 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/22 20:23:08 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

uint16_t	thrw_err(char *err_msg, char *err_file, int err_line)
{
	printf("%s:	%s:%d\n", err_msg, err_file, err_line);
	printf(USAGE_MSG);
	exit (EXIT_FAILURE);
}