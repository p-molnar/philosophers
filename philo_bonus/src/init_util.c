/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/05 10:24:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/05 10:24:47 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

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
		thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__);
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
