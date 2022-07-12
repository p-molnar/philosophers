/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_consts.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 16:40:19 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/29 12:10:50 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_CONSTS_H
# define PHILO_CONSTS_H

# define QUEUE_SIZE 64
# define UNDEFINED -1

enum e_status {
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	ALL_EATEN,
};

enum e_error_msg {
	INVALID_INPUT=1,
	MALLOC_ERROR,
	MUTEX_ERROR,
	THREAD_ERROR,
};

enum e_log_status {
	NO_CONTENT,
	CREATED,
	PRINTED,
};

#endif