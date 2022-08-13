/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 14:01:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/14 00:06:47 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

bool	init_philo(t_philo *philo)
{
	sem_wait(philo->sim_data->sem[SEM_START]);
	sem_post(philo->sim_data->sem[SEM_START]);
	printf("philo id: %d\n", philo->id);
	return (EXIT_SUCCESS);
}

bool	start_processes(t_sim *data)
{
	uint32_t	i;
	uint32_t	*pid;
	int			wstatus;

	i = 0;
	pid = malloc(data->attr[N_PHILO] * sizeof(uint32_t));
	if (pid == NULL)
		thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__);
	sem_wait(data->sem[SEM_START]);
	while (i < (uint32_t)data->attr[N_PHILO])
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			init_philo(&data->philo[i]);
		}
		i++;
	}
	sem_post(data->sem[SEM_START]);
	i = 0;
	while (i < (uint32_t)data->attr[N_PHILO])
	{
		waitpid(pid[i], &wstatus, WIFEXITED(wstatus));
		i++;
	}
	return (EXIT_SUCCESS);
}
