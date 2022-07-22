/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:54:06 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/22 17:00:38 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	validate_arg(int argc, t_data *data)
{
	uint16_t	i;

	if (data->arg[N_PHILO] < 1)
		return (error_handler(INVALID_INPUT, "validate_arg"));
	i = 0;
	while (i < argc - 1)
	{
		if (data->arg[i] < 0)
			return (error_handler(INVALID_INPUT, "validate_arg"));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	parse_args(int argc, char *argv[], t_data *data)
{	
	uint16_t	i;

	if (argc < 5 || argc > 6)
		return (error_handler(INVALID_INPUT, "parse_args"));
	i = 1;
	while (i < argc)
	{
		data->arg[i - 1] = ft_atoi(argv[i]);
		data->arg[i] = 0;
		i++;
	}
	return (validate_arg(argc, data));
}
