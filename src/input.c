/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:54:06 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/16 00:57:39 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	validate_input(int argc, t_attr *attr)
{
	if (argc <= 6)
	{
		if (attr->philo_count < 0 ||
			attr->die_duration < 0 ||
			attr->eat_duration < 0 ||
			attr->sleep_duration < 0)
		{
			return (1);
		}
		if (argc == 6 && attr->required_eat_count < 0)
			return (1);
	}
	return (0);
}

bool	parse_input(int	argc, char *argv[], t_attr *attr)
{	
	attr->philo_count = ft_atoi(argv[1]);
	attr->die_duration = 1000 * ft_atoi(argv[2]);
	attr->eat_duration = 1000 * ft_atoi(argv[3]);
	attr->sleep_duration = 1000 * ft_atoi(argv[4]);
	if (argc == 6)
		attr->required_eat_count = ft_atoi(argv[5]);
	if (validate_input(argc, attr))
		return (1);
	return (0);
}