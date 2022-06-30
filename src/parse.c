/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:54:06 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/30 12:22:12 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	validate_args(int argc, t_sim_data *attr)
{
	if (attr->n_philo < 1 || attr->t_die < 0 || \
		attr->t_eat < 0 || attr->t_sleep < 0)
	{
		return (error_handler(INVALID_INPUT, NULL));
	}
	if (argc == 6 && attr->min_n_eat < 0)
		return (error_handler(INVALID_INPUT, NULL));
	return (EXIT_SUCCESS);
}

int	parse_args(int argc, char *argv[], t_sim_data *attr)
{	
	attr->n_philo = ft_atoi(argv[1]);
	attr->t_die = ft_atoi(argv[2]);
	attr->t_eat = ft_atoi(argv[3]);
	attr->t_sleep = ft_atoi(argv[4]);
	attr->min_n_eat = -1;
	if (argc == 6)
		attr->min_n_eat = ft_atoi(argv[5]);
	return (validate_args(argc, attr));
}
