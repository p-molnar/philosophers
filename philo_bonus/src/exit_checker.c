/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_checker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 10:27:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/09 11:52:50 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <string.h>
#include <errno.h>

bool	close_exit_checker(t_sim *data, uint16_t i)
{
	pthread_join(data->checker_thread[i], NULL);
	pthread_detach(data->checker_thread[i]);
	return (EXIT_SUCCESS);
}

void	*child_exit_status_checker(void *d)
{
	t_data_coll	*coll;
	int16_t		pid;
	int			status;

	coll = d;
	pid = waitpid(coll->philo_pid, &status, WNOHANG);
	while (pid != coll->philo_pid)
	{
		// printf("checked pid: %d, ret: %d\n", coll->philo_pid, pid);
		pid = waitpid(coll->philo_pid, &status, WNOHANG);
	}
	if (pid < 0)
	{
		printf("error: %s\n", strerror(errno));
		thrw_err(PROCESS_ERR_MSG, __FILE__, __LINE__);
	}
	else if (WEXITSTATUS(status) == DIED)
	{
		printf("B_philo %d died\n", coll->philo_idx);
		kill_all_child_process(coll->data);
		return (EXIT_SUCCESS);
	}
	printf("%d exited?\n", pid);
	return (NULL);
}

bool	start_exit_checker(t_sim *data, uint16_t i)
{
	t_data_coll	d;
	int16_t		ret_val;

	d.data = data;
	d.philo_idx = i;
	d.philo_pid = data->child_pid_arr[i];
	ret_val = pthread_create(&data->checker_thread[i], NULL, \
		&child_exit_status_checker, (void *)&d);
	return (ret_val != 0);
}
