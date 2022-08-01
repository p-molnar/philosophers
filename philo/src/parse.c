/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:54:06 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/01 14:43:08 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static uint16_t	ft_isspace(int c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r');
}

static uint16_t	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int32_t	ft_atoi(char *str)
{
	int			num;
	int			sign;
	const int	coeff[2] = {+1, -1};

	num = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str && (*str == '-' || *str == '+'))
		sign = coeff[(*str++ == '-')];
	while (*str && ft_isdigit(*str))
		num = 10 * num + (*str++ - '0');
	return (sign * num);
}

uint16_t	validate_arg(int argc, t_sim *data)
{
	uint16_t	i;

	if (data->attr[N_PHILO] < 1)
		return (thrw_err(INPUT_ERR_MSG, __FILE__, __LINE__));
	i = 0;
	while (i < argc - 2)
	{
		if (data->attr[i] < 0)
			return (thrw_err(INPUT_ERR_MSG, __FILE__, __LINE__));
		i++;
	}
	return (EXIT_SUCCESS);
}

uint16_t	parse_args(int argc, char *argv[], t_sim *data)
{	
	uint16_t	i;

	if (argc < 5 || argc > 6)
		return (thrw_err(INPUT_ERR_MSG, __FILE__, __LINE__));
	i = 1;
	while (i < argc)
	{
		data->attr[i - 1] = ft_atoi(argv[i]);
		data->attr[i] = UNDEFINED;
		i++;
	}
	return (validate_arg(argc, data));
}
