/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphore.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:37:46 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/22 10:51:27 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

char	*gen_sem_name(char *id)
{
	char		*name;
	uint16_t	i;

	name = malloc (32 * sizeof(char));
	if (name == NULL)
		handle_err(MALLOC_ERR_MSG, __FILE__, __LINE__, NULL);
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
		handle_err(MALLOC_ERR_MSG, __FILE__, __LINE__, NULL);
	i = 0;
	name = gen_sem_name(id);
	sem = sem_open(name, O_CREAT | O_EXCL, 000664, 1);
	if (sem == SEM_FAILED)
		handle_err(SEM_ERR_MSG, __FILE__, __LINE__, NULL);
	sem_unlink(name);
	free (id);
	return (sem);
}

bool	semaphore_op(t_sim *data, uint8_t mode)
{
	uint16_t		i;
	const int16_t	oflag = O_CREAT | O_EXCL;
	const t_sem_ht	ht[SEM__COUNT] = {[START_LOCK] = {"/sem_start", 0}, \
								[PRINTER_LOCK] = {"/sem_print", 0}, \
								[CHECKER_LOCK] = {"/sem_checker", 0}, \
								[FORK] = {"/sem_fork", data->attr[N_PHILO]}};

	i = 0;
	while (i < SEM__COUNT)
	{
		if (mode == OPEN)
		{
			data->generic_sem[i] = sem_open(ht[i].name, \
				oflag, 0660, ht[i].init_val);
			if (data->generic_sem[i] == SEM_FAILED)
				return (handle_err(SEM_ERR_MSG, __FILE__, __LINE__, data));
		}
		else if (mode == CLOSE)
			sem_close(data->generic_sem[i]);
		else if (mode == UNLINK)
			sem_unlink(ht[i].name);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	unlock_gen_semaphores(t_sim *data)
{
	sem_post(data->generic_sem[START_LOCK]);
	sem_post(data->generic_sem[PRINTER_LOCK]);
	precise_msleep(1);
	sem_post(data->generic_sem[CHECKER_LOCK]);
}
