/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/11 14:01:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/17 22:55:37 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

bool	init_philo(t_philo *philo)
{
	int	sval;
	sem_wait(philo->sim_data->sem[SEM_START]);
	sem_getvalue((philo->sim_data->sem[SEM_START]), &sval);
	printf("sem_val - wait: %d\n", sval);
	sem_post(philo->sim_data->sem[SEM_START]);
	sem_getvalue((philo->sim_data->sem[SEM_START]), &sval);
	printf("sem_val - post: %d\n", sval);
	printf("philo id: %d\n", philo->id);
	return (EXIT_SUCCESS);
}

bool	start_processes(t_sim *data)
{
	uint32_t	i;
	uint32_t	*pid;
	int			sval;
	int			wstatus;

	i = 0;
	pid = malloc(data->attr[N_PHILO] * sizeof(uint32_t));
	if (pid == NULL)
		thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__);
	while (i < (uint32_t)data->attr[N_PHILO])
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			init_philo(&data->philo[i]);
			return (EXIT_SUCCESS);
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
