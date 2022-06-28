/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_consts.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 16:40:19 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/28 12:46:52 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_CONSTS_H
# define PHILO_CONSTS_H
# define QUEUE_SIZE 64
enum e_status {
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	EATEN_ENOUGH,
	EXIT_DIED,
	UNDEFINED,
};

enum e_error_msg {
	INVALID_INPUT=1,
	MALLOC_ERROR,
	MUTEX_ERROR,
	THREAD_ERROR,
};

enum e_fork_status {
	AVAILABLE,
	TAKEN,
};

#endif