/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_util.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/05 10:24:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/22 09:27:09 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

uint16_t	ft_isspace(int c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r');
}

uint16_t	ft_isdigit(int c)
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

uint32_t	ft_strlen(char *s)
{
	uint32_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

char	*ft_itoa(int16_t num)
{
	char		*s;
	uint16_t	i;

	s = malloc(sizeof(char) * 4);
	if (s == NULL)
		handle_err(MALLOC_ERR_MSG, __FILE__, __LINE__, NULL);
	i = 0;
	while (i < 4)
	{
		s[i] = num % 10 + '0';
		num /= 10;
		i++;
	}
	s[i] = '\0';
	return (s);
}
