/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 20:58:51 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/21 17:34:06 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

void	init_resources(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		data->philo_sem[i] = gen_philo_sem(i);
		i++;
	}
}

char	*gen_sem_name(char *id)
{
	char		*name;
	uint16_t	i;

	name = malloc (32 * sizeof(char));
	if (name == NULL)
		thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__);
	i = 0;
	while (i < 7)
	{
		name[i] = "/philo_"[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(id))
	{
		name[i + 7] = id[i];
		i++;
	}
	name[i + 7] = '\0';
	return (name);
}

sem_t	*gen_philo_sem(uint16_t philo_idx)
{
	char		*id;
	char		*name;
	uint16_t	i;
	sem_t		*sem;

	id = ft_itoa(philo_idx);
	if (id == NULL)
		thrw_err(MALLOC_ERR_MSG, __FILE__, __LINE__);
	i = 0;
	name = gen_sem_name(id);
	sem = sem_open(name, O_CREAT | O_EXCL, 000664, 1);
	if (sem == SEM_FAILED)
		thrw_err(SEM_ERR_MSG, __FILE__, __LINE__);
	sem_unlink(name);
	free (id);
	return (sem);
}

void	init_philo(t_sim *data, uint16_t i)
{
	data->philo.id = i + 1;
	data->philo.n_forks_in_hand = 0;
	data->philo.eat_count = 0;
	data->philo.sim_data = data;
	data->philo.self_lock = data->philo_sem[i];
}
