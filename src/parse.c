/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:54:06 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/19 22:02:52 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	validate_args(int argc, t_attr *attr)
{
	if (attr->philo_count < 2 || attr->die_duration < 0 || \
		attr->eat_duration < 0 || attr->sleep_duration < 0)
	{
		return (error_handler(INVALID_INPUT));
	}
	if (argc == 6 && attr->min_eat_count < 0)
		return (error_handler(INVALID_INPUT));
	return (EXIT_SUCCESS);
}

int	parse_args(int argc, char *argv[], t_attr *attr)
{	
	attr->philo_count = ft_atoi(argv[1]);
	attr->die_duration = 1000 * ft_atoi(argv[2]);
	attr->eat_duration = 1000 * ft_atoi(argv[3]);
	attr->sleep_duration = 1000 * ft_atoi(argv[4]);
	attr->min_eat_count = -1;
	if (argc == 6)
		attr->min_eat_count = ft_atoi(argv[5]);
	return (validate_args(argc, attr));
}
