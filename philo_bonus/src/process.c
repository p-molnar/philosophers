/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 14:01:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/12 15:04:50 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

void	philo(uint16_t i)
{
	int	idx = 0;

	while (idx < 5)
	{
		printf("%d is running\n", i);
		sleep(1);
		idx++;
	}
	exit(EXIT_SUCCESS);
}

bool	start_processes(t_sim *data)
{
	uint32_t	i;
	uint32_t	*pid;

	i = 0;
	pid = malloc(data->attr[N_PHILO] * sizeof(uint32_t));
	if (pid == NULL)
		thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__);
	while (i < (uint32_t)data->attr[N_PHILO])
	{

		pid[i] = fork();
		if (pid[i] < 0)
			thrw_err (PROCESS_ERR_MSG, __FILE__, __LINE__);
		if (pid[i] == 0)
		{
			printf("abc\n");
			return (EXIT_SUCCESS);
		}
		i++;
	}
	printf("abc\n");
	return (EXIT_SUCCESS);
}
