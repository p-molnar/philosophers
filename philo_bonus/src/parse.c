/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:54:06 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/22 09:29:00 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

uint16_t	validate_arg(int argc, t_sim *data)
{
	uint16_t	i;

	if (data->attr[N_PHILO] < 1)
		return (handle_err(INPUT_ERR_MSG, __FILE__, __LINE__, NULL));
	i = 0;
	while (i < argc - 2)
	{
		if (data->attr[i] < 0)
			return (handle_err(INPUT_ERR_MSG, __FILE__, __LINE__, NULL));
		i++;
	}
	return (EXIT_SUCCESS);
}

uint16_t	parse_args(int argc, char *argv[], t_sim *data)
{	
	uint16_t	i;

	if (argc < 5 || argc > 6)
		return (handle_err(INPUT_ERR_MSG, __FILE__, __LINE__, NULL));
	i = 1;
	while (i < argc)
	{
		data->attr[i - 1] = ft_atoi(argv[i]);
		data->attr[i] = UNDEFINED;
		i++;
	}
	return (validate_arg(argc, data));
}
