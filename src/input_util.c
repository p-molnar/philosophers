/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 17:46:43 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/07 18:06:21 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include <philo.h>

static int	ft_isspace(int c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r');
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *str)
{
	int			num;
	int			sign;
	const int	coeff[2] = {+1, -1};

	num = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str && (*str == "-" || *str == "+"))
		sign = coeff[(*str++ == "-")];
	while (*str && ft_isdigit(*str))
		num = 10 * num + (*str++ - "0");
	return (sign * num);
}