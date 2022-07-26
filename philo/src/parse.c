/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:54:06 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/25 14:13:56 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	validate_arg(int argc, t_sim *data)
{
	uint16_t	i;

	if (data->attr[N_PHILO] < 1)
		return (thrw_err(INPUT_ERR_MSG, __FILE__,__LINE__));
	i = 0;
	while (i < argc - 1)
	{
		if (data->attr[i] < 0)
			return (thrw_err(INPUT_ERR_MSG, __FILE__,__LINE__));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	parse_args(int argc, char *argv[], t_sim *data)
{	
	uint16_t	i;

	if (argc < 5 || argc > 6)
		return (thrw_err(INPUT_ERR_MSG, __FILE__,__LINE__));
	i = 1;
	while (i < argc)
	{
		data->attr[i - 1] = ft_atoi(argv[i]);
		data->attr[i] = 0;
		i++;
	}
	return (validate_arg(argc, data));
}
