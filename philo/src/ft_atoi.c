/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 19:00:19 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/26 23:07:21 by pmolnar       ########   odam.nl         */
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

int32_t	ft_atoi(char *str)
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
